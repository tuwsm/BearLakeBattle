// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FlexController.h"
#include "AsyncActionCalibrateFlex.generated.h"

class UFlexController;
/**
 * 
 */
UCLASS()
class LIMBITLESSBLUETOOTHPLUGIN_API UAsyncActionCalibrateFlex : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true", Category = "Calibration"))
	static UAsyncActionCalibrateFlex* AsyncCalibrateFlexController(UFlexController* FlexController);

	UPROPERTY(BlueprintAssignable)
	FOnCalibrationStartedSignature OnRestCalibrationStarted{};

	UPROPERTY(BlueprintAssignable)
	FOnCalibrationStartedSignature OnFlexCalibrationStarted{};

	UPROPERTY(BlueprintAssignable)
	FOnCalibrationEndedSignature OnCalibrationComplete{};

	virtual void Activate() override;
	
private:
	TWeakObjectPtr<UFlexController> FlexController;

	UFUNCTION()
	void OnRestStarted(float Duration);

	UFUNCTION()
	void OnFlexStarted(float Duration);

	UFUNCTION()
	void OnFlexFinished();

};
