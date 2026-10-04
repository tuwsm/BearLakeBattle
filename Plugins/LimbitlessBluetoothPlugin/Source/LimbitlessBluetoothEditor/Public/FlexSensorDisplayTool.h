// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
//#include "Blutility/Classes/EditorUtilityWidget.h"
#include "FlexSensorDisplayTool.generated.h"

class UFlexController;

USTRUCT(BlueprintType)
struct FSensorDisplayData
{
	GENERATED_BODY()

	FSensorDisplayData() = default;
	
	FSensorDisplayData(int InitialSize)
	{
		EMGReadings.Init(0, InitialSize);
		
		AngularVelocityX.Init(0, InitialSize);
		AngularVelocityY.Init(0, InitialSize);
		AngularVelocityZ.Init(0, InitialSize);

		ProperAccelerationX.Init(0, InitialSize);
		ProperAccelerationY.Init(0, InitialSize);
		ProperAccelerationZ.Init(0, InitialSize);

		CoordinateAccelerationX.Init(0, InitialSize);
		CoordinateAccelerationY.Init(0, InitialSize);
		CoordinateAccelerationZ.Init(0, InitialSize);
	}

	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	TArray<float> EMGReadings{};

	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	TArray<float> AngularVelocityX{};
	
	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	TArray<float> AngularVelocityY{};

	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	TArray<float> AngularVelocityZ{};

	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	TArray<float> ProperAccelerationX{};
	
	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	TArray<float> ProperAccelerationY{};

	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	TArray<float> ProperAccelerationZ{};

	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	TArray<float> CoordinateAccelerationX{};

	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	TArray<float> CoordinateAccelerationY{};
	
	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	TArray<float> CoordinateAccelerationZ{};
};
/**
 * 
 */
UCLASS()
class LIMBITLESSBLUETOOTHEDITOR_API UFlexSensorDisplayTool : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Sensor Data")
	void RefreshDevices();

	UPROPERTY(EditDefaultsOnly, Category = "Sensor Data")
	int MaxValuesStored{ 250 };

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	TMap<UFlexController*, FSensorDisplayData> ControllerData{};

	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	TArray<UFlexController*> TrackedControllers{};

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void AddDataToArray(TArray<float>& Array, float Data, int MaxSize);
};
