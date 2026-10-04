// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Menu.h"
#include "FlexCalibrationMenu.generated.h"

class UGraphPlot;
class UFlexController;

/**
 * 
 */
UCLASS()
class BASHCORE_API UFlexCalibrationMenu : public UMenu
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Flex Calibration Menu")
	void SetTrackedController(UFlexController* Controller);

	UFUNCTION(BlueprintCallable, Category = "Flex Calibration Menu")
	UFlexController* GetTrackedController() const;
	
protected:
	// How many flex values to store to show in calibration graph
	UPROPERTY(EditAnywhere, Category = "Flex Calibration Menu")
	int NumStoredValues{};
	
	virtual void NativeConstruct() override;
	virtual void OnOpenMenu(TScriptInterface<IBashController> InOwningPlayer) override;
	virtual void OnCloseMenu() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Flex Calibration Menu")
	const TArray<float>& GetRecentFlexData() const { return FlexData; }

	UFUNCTION(BlueprintCallable, Category = "Flex Calibration Menu")
	float GetTrackedRestThreshold() const;

private:
	TWeakObjectPtr<UFlexController> TrackedController{};

	TArray<float> FlexData{};
};
