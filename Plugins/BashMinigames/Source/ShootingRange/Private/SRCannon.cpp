// Fill out your copyright notice in the Description page of Project Settings.


#include "SRCannon.h"
#include "Kismet/KismetMathLibrary.h"
#include "MinigameBase.h"
#include "MinigameCapture.h"
#include "MinigameCoreBlueprintLibrary.h"
#include "Player/PlayerRotationComponent.h"

ASRCannon::ASRCannon()
{
	RotationComponent = CreateDefaultSubobject<UPlayerRotationComponent>("Rotation Component");
	
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	BarrelRoot = CreateDefaultSubobject<USceneComponent>("Barrel Root");
	BarrelRoot->SetupAttachment(GetRootComponent());

	BaseRoot = CreateDefaultSubobject<USceneComponent>("Base Root");
	BaseRoot->SetupAttachment(GetRootComponent());

	BaseSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Base Mesh");
	BaseSkeletalMesh->SetupAttachment(BaseRoot);

	BulletSpawn = CreateDefaultSubobject<USceneComponent>("Bullet Spawn");
	BulletSpawn->SetupAttachment(BarrelRoot);
}

void ASRCannon::BeginPlay()
{
	Super::BeginPlay();
	MinigameCamera = Minigame->GetCamera(PlayerNumber);
	RotationComponent->ResetInitialOrientation();
}

void ASRCannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AttackCooldownTimer -= DeltaTime;

	// Set cannon rotation to make it seem like it's aiming at the crosshair
	// Only visual - not important for actual aiming
	FVector CrosshairPosition{};
	GetCrosshairPosition(1, CrosshairPosition);
	FRotator Rotation = UKismetMathLibrary::MakeRotFromX(CrosshairPosition - GetActorLocation());
	SetCannonRotation(Rotation);
}

void ASRCannon::Fire(int Layer)
{
	if (AttackCooldownTimer > 0 || !Minigame->IsInProgress()) { return; }
	AttackCooldownTimer = AttackCooldown;

	FVector CrosshairPosition;
	if (!GetCrosshairPosition(Layer, CrosshairPosition)) { return; }

	FVector BulletVelocity = GetArcVelocity(BulletSpawn->GetComponentLocation(), CrosshairPosition);
	ShootProjectile(BulletVelocity);
}

FVector ASRCannon::GetStraightVelocity(const FVector& Source, const FVector& Target)
{
	return BulletSpeed * (Target - Source).GetSafeNormal();
}

FVector ASRCannon::GetArcVelocity(const FVector& Source, const FVector& Target)
{
	FVector Velocity{};
	float Time{};
	if (UMinigameCoreBlueprintLibrary::GetProjectileTrajectoryVelocityFromLaunchSpeed(
		this, Source, Target, BulletSpeed, false,
		Velocity, Time))
	{
		return Velocity;
	}
	else
	{
		// A valid trajectory is not possible. Fallback to straight line.
		return GetStraightVelocity(Source, Target);
	}
}

bool ASRCannon::GetCrosshairPosition(int Layer, FVector& OutPosition)
{
	TArray<AActor*> IgnoreActors = GetDepthLayers();
	if (MinigameCamera == nullptr || Layer < 0 || IgnoreActors.Num() < Layer) { return false; }


	// Don't ignore the layer we're trying to target
	if (Layer < IgnoreActors.Num())
	{
		IgnoreActors.RemoveAt(Layer);
	}
	IgnoreActors.Add(this);

	// Get a point in the direction of where the camera is facing
	FVector RaycastEnd = 1000 * RotationComponent->GetDirectionFromCamera(MinigameCamera->GetActorQuat());

	// Perform line trace
	FCollisionQueryParams Params{};
	Params.AddIgnoredActors(IgnoreActors);
	FHitResult Res{};
	if (GetWorld()->LineTraceSingleByChannel(Res, MinigameCamera->GetActorLocation(), RaycastEnd, ECollisionChannel::ECC_Camera, Params))
	{
		OutPosition = Res.ImpactPoint;
		return true;
	}
	return false;
}

void ASRCannon::SetCannonRotation(const FRotator& Rotator)
{
	CannonRotation = Rotator;
	BarrelRoot->SetWorldRotation(Rotator);
	
	FRotator BaseRotator = FRotator{ 0, Rotator.Yaw, 0 };
	BaseRoot->SetWorldRotation(BaseRotator);
}