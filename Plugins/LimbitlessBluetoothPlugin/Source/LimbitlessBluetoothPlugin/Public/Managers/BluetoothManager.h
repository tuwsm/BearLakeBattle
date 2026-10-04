// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BluetoothManager.generated.h"

class UFlexController;

DECLARE_DELEGATE_OneParam(FOnFlexFoundSignature, UFlexController*);
DECLARE_DELEGATE(FOnFlexConnectedSignature);
DECLARE_DELEGATE(FOnFlexDisconnectedSignature);
DECLARE_DELEGATE_OneParam(FOnFlexConnectionErrorSignature, FString);
DECLARE_DELEGATE_OneParam(FOnFlexDisconnectionErrorSignature, FString);
DECLARE_DELEGATE(FOnFlexServiceSetSignature);

// This class does not need to be modified.
UINTERFACE()
class LIMBITLESSBLUETOOTHPLUGIN_API UBluetoothManager : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LIMBITLESSBLUETOOTHPLUGIN_API IBluetoothManager
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Init(const FString& writeCharacteristic);
	virtual void Deinit();

	/*
	 * Set a filter for devices to search for
	 */
	virtual void SetServiceUUIDsToScanFor(const TArray<FString>& filteredServiceUUIDs);
	
	
	/**
	* Find nearby BLE devices with specific services
	*/
	virtual void ScanForDevices(const FOnFlexFoundSignature& onDeviceFoundCallback);

	/**
	* Stop searching for nearby BLE devices
	*/
	virtual void StopScan();
	
	/**
	* Connect to specified BLE device
	*/
	virtual void ConnectToDevice(UFlexController* device, const TArray<FString> characteristicIds,
		const FOnFlexConnectedSignature& onDeviceConnectedCallback, const FOnFlexConnectionErrorSignature& onFailToConnectDeviceCallback, const FOnFlexServiceSetSignature& onServiceSetCallback) const;

	/**
	* Disconnect specified BLE device
	*/
	virtual void DisconnectDevice(const UFlexController* device,
	const FOnFlexDisconnectedSignature& onDeviceDisconnectedCallback, const FOnFlexDisconnectionErrorSignature& onFailToDisconnectDeviceCallback) const;
};
