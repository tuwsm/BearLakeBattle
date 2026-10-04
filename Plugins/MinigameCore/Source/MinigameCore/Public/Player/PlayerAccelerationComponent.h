// Copyright Limbitless Solutions, Inc. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerAccelerationComponent.generated.h"

class UPlayerRotationComponent;
class UInputAction;
class UEnhancedInputLocalPlayerSubsystem;

DECLARE_DYNAMIC_DELEGATE(FOnMovementTriggeredSignature);
DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FEvaluateMovementSignature, FVector, CoordinateAcceleration);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINIGAMECORE_API UPlayerAccelerationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerAccelerationComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Player Acceleration")
	void ListenForMovement(FEvaluateMovementSignature EvaluateMovement, FOnMovementTriggeredSignature OnMovementTriggered);

	// Returns the coordinate acceleration of the player's flex controller in m/s^2. Coordinate acceleration is not affected by gravity
	// and represents acceleration experienced by the device relative to Earth. Useful for game logic.
	UFUNCTION(BlueprintCallable, Category = "Player Acceleration")
	virtual FVector GetCoordinateAcceleration() const { return CoordinateAcceleration; }

	UFUNCTION(BlueprintCallable, Category = "Player Acceleration")
	virtual FVector GetAccelerationInputValue() const;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void InitializeComponent() override;

	TObjectPtr<UPlayerRotationComponent> RotationComponent{};
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem{};
	TObjectPtr<UInputAction> RotationAction{};
	TObjectPtr<UInputAction> AccelerationAction{};

	TMap<FEvaluateMovementSignature, FOnMovementTriggeredSignature> MovementTriggers{};
	
	FVector CoordinateAcceleration{};
	
	FQuat GetRotation() const;
};
