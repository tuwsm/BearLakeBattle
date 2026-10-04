// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SensorData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BluetoothManagerSubsystem.generated.h"

class ALimbitlessPlayerController;
class UFlexController;
class ULimbitlessBluetoothManager;

using Device = UFlexController*;
using DeviceId = FString;

DECLARE_DELEGATE_OneParam(FOnConnectionErrorDelegate, FString);
DECLARE_DELEGATE(FOnServiceSetDelegate)

/**
 * 
 */
UCLASS()
class PLATFORMMANAGER_API UBluetoothManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	
	// Gets all the colors that can be assigned to devices
	UFUNCTION(BlueprintGetter)
	const TArray<EFlexColor>& GetColors() const { return DeviceColors; }

	// Starts a bluetooth scan
	UFUNCTION(BlueprintCallable, Category = "Scanning")
	void StartScan();
	UFUNCTION(BlueprintCallable, Category = "Scanning")
	void StopScan();

	UFUNCTION(BlueprintCallable, Category = "Assignment")
	void AssignControllerToPlayer(ALimbitlessPlayerController* player, UFlexController* device);

	const TArray<UFlexController*>& GetConnectedControllers() const { return ConnectedControllers; } 
protected:
	// Information about connected devices
	UPROPERTY(BlueprintReadOnly, Category = "Connected Controllers")
	TArray<UFlexController*> UnpairedFlexDevices{};

	UPROPERTY(BlueprintReadOnly, Category = "Connected Controllers")
	TArray<UFlexController*> PairedFlexDevices{};

	UPROPERTY(BlueprintReadOnly, Category = "Connected Controllers")
	TArray<UFlexController*> ConnectedControllers{};
	
private:
	// Properties to set ----

	// Colors automatically assigned to flex devices in order of connection. 
	// First color is reserved for unassigned players and isn't assigned to flex devices
	UPROPERTY(BlueprintGetter = GetColors, Category = "Assignment")
	TArray<EFlexColor> DeviceColors{ EFlexColor::EFC_White, EFlexColor::EFC_Red, EFlexColor::EFC_Cyan, EFlexColor::EFC_Green, EFlexColor::EFC_Yellow};

	// --------------------
	
	UPROPERTY()
	TObjectPtr<ULimbitlessBluetoothManager> BLEManager{};
	
	// Maps the player number to the color index corresponding to a device
	TMap<int, int> PlayerColorAssignment{};

	// Map of color index to the assigned device
	TMap<int, Device> DeviceColorAssignment;


	void OnDeviceConnect(Device Device);
	void OnDeviceDisconnect(Device Device);
	static bool DoesFlexControllerArrayContainColor(EFlexColor color, const TArray<UFlexController*>& controllers);

	EFlexColor GetNextColor() const;


};

