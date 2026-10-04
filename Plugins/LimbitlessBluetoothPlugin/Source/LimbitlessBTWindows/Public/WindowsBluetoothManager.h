// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <winrt/base.h>

#include "CoreMinimal.h"
#include "Managers/BluetoothManager.h"
#include "UObject/Object.h"
#include "WindowsBluetoothManager.generated.h"

class UWinBLEManager;
/**
 * 
 */
UCLASS()
class LIMBITLESSBTWINDOWS_API UWindowsBluetoothManager : public UObject, public IBluetoothManager
{
	GENERATED_BODY()
public:
	void CreateWinBLEManager();
	virtual void Init(const FString& writeCharacteristic) override;
	virtual void Deinit() override;
	
	winrt::guid FStringToWinrtGUID(const FString& fstr) const;
	void ConvertFStringArrayToGuidArray(const TArray<FString>& fstrings, TArray<winrt::guid>& guids) const;

	virtual void SetServiceUUIDsToScanFor(const TArray<FString>& filteredServiceUUIDs) override;
	virtual void ScanForDevices(const FOnFlexFoundSignature& onDeviceFoundCallback) override;
	virtual void StopScan() override;
	virtual void ConnectToDevice(UFlexController* device, const TArray<FString> characteristicIds, const FOnFlexConnectedSignature& onDeviceConnectedCallback, const FOnFlexConnectionErrorSignature& onFailToConnectDeviceCallback, const FOnFlexServiceSetSignature& onServiceSetCallback) const override;
	virtual void DisconnectDevice(const UFlexController* device, const FOnFlexDisconnectedSignature& onDeviceDisconnectedCallback, const FOnFlexDisconnectionErrorSignature& onFailToDisconnectDeviceCallback) const override;
	
private:
	UPROPERTY()
	TObjectPtr<UWinBLEManager> WinBLEManager;

	TMap<uint64_t, UFlexController*> CreatedControllers{};
	
	winrt::guid WriteCharacteristicUUID;
	
};
