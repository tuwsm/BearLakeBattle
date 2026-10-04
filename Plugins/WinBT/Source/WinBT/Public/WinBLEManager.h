#pragma once

#include "CoreMinimal.h"
#include <winrt/Windows.Devices.Bluetooth.Advertisement.h>
#include <winrt/Windows.Devices.Bluetooth.h>
#include <winrt/Windows.Devices.Bluetooth.GenericAttributeProfile.h>
#include "BtDeviceHolder.h"
#include "WinBLEManager.generated.h"



namespace  winrt::Windows::Devices::Bluetooth::GenericAttributeProfile
{
	struct GattCharacteristic;
}

struct GattDeviceService;

using winrt::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement;
using winrt::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs;
using winrt::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher;
using winrt::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs;
using winrt::Windows::Devices::Bluetooth::BluetoothLEDevice;

DECLARE_DELEGATE_OneParam(FOnDeviceFoundSignature, BtDeviceHolder&);
DECLARE_DELEGATE(FOnDeviceConnectedSignature);
DECLARE_DELEGATE(FOnDeviceDisconnectedSignature);
DECLARE_DELEGATE_OneParam(FOnConnectionErrorSignature, FString);
DECLARE_DELEGATE_OneParam(FOnDisconnectionErrorSignature, FString);
DECLARE_DELEGATE(FOnServiceSetSignature);


// ServiceUUIDs "0000FE84-0000-1000-8000-00805F9B34FB"
// CharacteristicUUID "0000FE84-0000-0001-8000-00805F9B34FB"

UCLASS()
class WINBT_API UWinBLEManager : public UObject
{
	GENERATED_BODY()

public:
	UWinBLEManager();
	

	void Init();
	void Deinit();

		
	void SetServiceUUIDsToScanFor(const TArray<winrt::guid>& filteredServiceUUIDs);
	
	
	/**
	* Find nearby BLE devices with specific services
	*/
	void ScanForDevices(const FOnDeviceFoundSignature& onDeviceFoundCallback);

	/**
	* Stop searching for nearby BLE devices
	*/
	void StopScan();
	
	/**
	* Connect to specified BLE device
	*/
	void ConnectToDevice(BtDeviceHolder& device, const TArray<winrt::guid> characteristicIds,
		const FOnDeviceConnectedSignature& onDeviceConnectedCallback, const FOnConnectionErrorSignature& onFailToConnectDeviceCallback, const FOnServiceSetSignature& onServiceSetCallback) const;

	/**
	* Disconnect specified BLE device
	*/
	void DisconnectDevice(const BtDeviceHolder& device,
		const FOnDeviceDisconnectedSignature& onDeviceDisconnectedCallback, const FOnDisconnectionErrorSignature& onFailToDisconnectDeviceCallback) const;
	void DisconnectAllDevices(const FOnDeviceDisconnectedSignature& onDeviceDisconnectedCallback) const;
protected:
	void DiscoverAndSubscribeToCharacteristics(BtDeviceHolder& device, const TArray<winrt::guid> characteristicIds, winrt::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService service, const FOnServiceSetSignature& onServiceSetCallback) const;


private:
	bool bIsInitialized = false;

	std::vector<std::unique_ptr<BtDeviceHolder>> FoundBluetoothDevices;
	
	BluetoothLEAdvertisementWatcher AdvertisementWatcher;
	
	TArray<winrt::guid> FilteredServiceUUIDs;

};
