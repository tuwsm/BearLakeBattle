// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FlexController.h"
#include "AsyncActionCalibrateIMU.generated.h"

/**
 * 
 */
UCLASS()
class LIMBITLESSBLUETOOTHPLUGIN_API UAsyncActionCalibrateIMU : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true", Category = "Calibration"))
	static UAsyncActionCalibrateIMU* AsyncCalibrateIMU(UFlexController* FlexController);

	UPROPERTY(BlueprintAssignable)
	FOnCalibrationStartedSignature OnCalibrationStarted{};

	UPROPERTY(BlueprintAssignable)
	FOnCalibrationEndedSignature OnCalibrationComplete{};

	virtual void Activate() override;;

private:
	TWeakObjectPtr<UFlexController> FlexController;

	UFUNCTION()
	void HandleCalibrationStart(float Duration);

	UFUNCTION()
	void HandleCalibrationEnd();
};
