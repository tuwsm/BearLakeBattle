// Copyright Limbitless Solutions, Inc. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PlayerRotationComponent.h"
#include "SimpleMovingAverage.h"
#include "PlayerRotationMovingAverageComponent.generated.h"

/**
 * Uses a simple moving average of rotation data to calculate delta rotations.
 * This effectively "zeros" the rotation continuously, removing the need to explicitly zero with ResetInitialOrientation()
 * Use if you need rotation/acceleration data for quick movements and actions without interrupting gameplay.
 * If you need aiming behavior, use the base UPlayerRotationComponent instead
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINIGAMECORE_API UPlayerRotationMovingAverageComponent : public UPlayerRotationComponent
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void ResetInitialOrientation() override;

protected:
	virtual void BeginPlay() override;

	// Number of samples to use in the average
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Rotation")
	int32 WindowSize{100};

private:
	TSimpleMovingAverage<FVector> DeltaXSMA{};
	TSimpleMovingAverage<FVector> DeltaYSMA{};

	void InitializeDeltaSMA();
};
