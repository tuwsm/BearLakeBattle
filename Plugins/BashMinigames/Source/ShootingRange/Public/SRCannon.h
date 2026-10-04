// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/MinigamePlayer.h"
#include "SRCannon.generated.h"

class AMinigameCapture;
class UPlayerRotationComponent;

/**
 * 
 */
UCLASS()
class SHOOTINGRANGE_API ASRCannon : public AMinigamePlayer
{
	GENERATED_BODY()

public:
	ASRCannon();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/**
	*	Returns true if the crosshair is aiming at an actor in the correct Layer
	*	
	*	@param Layer Index in the Layers array to search for
	*	@param OutPosition Out parameter where the worldspace of the crosshair is stored
	*/
	bool GetCrosshairPosition(int Layer, FVector& OutPosition);

	UFUNCTION(BlueprintCallable)
	FRotator GetCannonTargetRotation() const { return CannonRotation; }
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, BlueprintPure)
	TArray<AActor*> GetDepthLayers() const;

	UFUNCTION(BlueprintCallable)
	bool CanFire() const { return AttackCooldownTimer <= 0; }
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USceneComponent> BarrelRoot;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USceneComponent> BaseRoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> BulletSpawn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> BaseSkeletalMesh;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UPlayerRotationComponent> RotationComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BulletSpeed;

	UFUNCTION(BlueprintImplementableEvent)
	void ShootProjectile(const FVector& Velocity);

	UFUNCTION(BlueprintCallable)
	void Fire(int Layer);

	UPROPERTY(BlueprintReadOnly)
	AMinigameCapture* MinigameCamera;
	
private:
	float AttackCooldownTimer;
	FRotator CannonRotation{};

	void SetCannonRotation(const FRotator& Rotation);

	// Get velocity to shoot a projectile straight at the target
	FVector GetStraightVelocity(const FVector& Source, const FVector& Target);

	// Get velocity to shoot a projectile that arcs from gravity
	FVector GetArcVelocity(const FVector& Source, const FVector& Target);
};
