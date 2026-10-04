// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Managers/BluetoothManager.h"
#include "UObject/Object.h"
#include "LimbitlessBluetoothManager.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMMANAGER_API ULimbitlessBluetoothManager : public UObject, public IBluetoothManager
{
	GENERATED_BODY()
public:
	void Initialize();
	void Deinitialize();

	virtual void SetServiceUUIDsToScanFor(const TArray<FString>& filteredServiceUUIDs) override;
	virtual void ScanForDevices(const FOnFlexFoundSignature& onDeviceFoundCallback) override;
	virtual void StopScan() override;
	virtual void ConnectToDevice(UFlexController* device, const TArray<FString> characteristicIds, const FOnFlexConnectedSignature& onDeviceConnectedCallback, const FOnFlexConnectionErrorSignature& onFailToConnectDeviceCallback, const FOnFlexServiceSetSignature& onServiceSetCallback) const override;
	virtual void DisconnectDevice(const UFlexController* device, const FOnFlexDisconnectedSignature& onDeviceDisconnectedCallback, const FOnFlexDisconnectionErrorSignature& onFailToDisconnectDeviceCallback) const override;

	TArray<FString>& GetDefaultServiceUUIDS(){return ServiceUUIDs;}
	TArray<FString>& GetDefaultCharacteristicIds(){return CharacteristicUUIDs;}
private:

	TArray<FString> ServiceUUIDs { TEXT("0000FE84-0000-1000-8000-00805F9B34FB") };
	TArray<FString> CharacteristicUUIDs{ TEXT("0000FE84-0000-0001-8000-00805F9B34FB") };
	
	TScriptInterface<IBluetoothManager> CreateBluetoothManager();
	
	UPROPERTY()
	TScriptInterface<IBluetoothManager> BLEManager{};
	
	void OnDeviceConnected(UFlexController* device, const FOnFlexConnectedSignature& next) const;
};
