// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Queue.h"
#include "Managers/BluetoothManager.h"
#include "UObject/Object.h"
#include "AndroidBluetoothManager.generated.h"

class IBLEManagerInterface;
class UFlexController;
class IBLEDeviceInterface;
/**
 * 
 */
UCLASS()
class LIMBITLESSBTANDROID_API UAndroidBluetoothManager : public UObject, public IBluetoothManager, public FTickableGameObject
{
	GENERATED_BODY()
public:
	virtual void Init(const FString& writeCharacteristic) override;
	virtual void Deinit() override;

	virtual void SetServiceUUIDsToScanFor(const TArray<FString>& filteredServiceUUIDs) override;
	virtual void ScanForDevices(const FOnFlexFoundSignature& onDeviceFoundCallback) override;
	virtual void StopScan() override;
	virtual void ConnectToDevice(UFlexController* device, const TArray<FString> characteristicIds, const FOnFlexConnectedSignature& onDeviceConnectedCallback, const FOnFlexConnectionErrorSignature& onFailToConnectDeviceCallback, const FOnFlexServiceSetSignature& onServiceSetCallback) const override;
	virtual void DisconnectDevice(const UFlexController* device, const FOnFlexDisconnectedSignature& onDeviceDisconnectedCallback, const FOnFlexDisconnectionErrorSignature& onFailToDisconnectDeviceCallback) const override;

	virtual bool IsTickable() const override;
	virtual bool IsTickableInEditor() const override;
	virtual bool IsTickableWhenPaused() const override;
	virtual bool IsAllowedToTick() const override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override { return Super::GetStatID(); }
private:
	TScriptInterface<IBLEManagerInterface> BLEManager;
	TMap<FString, UFlexController*> CreatedControllers{};
	FString WriteCharacteristic;

	
	FOnFlexFoundSignature OnDeviceFoundCallback;
	TQueue<TScriptInterface<IBLEDeviceInterface>, EQueueMode::Mpsc> FoundDeviceQueue;

};
