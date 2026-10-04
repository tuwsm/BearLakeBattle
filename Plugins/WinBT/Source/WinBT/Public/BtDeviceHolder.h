#pragma once
#include <winrt/Windows.Devices.Bluetooth.h>
#include <winrt/Windows.Devices.Bluetooth.GenericAttributeProfile.h>
#include <vector>
#include <stdint.h>
#include "Containers/Array.h"
#include "Delegates/Delegate.h"

namespace winrt::Windows::Devices::Bluetooth::GenericAttributeProfile
{
	struct GattCharacteristic;
}

namespace winrt
{
	struct guid;
}

DECLARE_DELEGATE_OneParam(FOnReceivedDataSignature, TArray<uint8_t>&)

class WINBT_API BtDeviceHolder
{
public:
	BtDeviceHolder(const winrt::Windows::Devices::Bluetooth::BluetoothLEDevice& device);
	~BtDeviceHolder();
	void AddTrackedCharacteristic(winrt::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic characteristic);

	bool operator==(BtDeviceHolder const& other) const;
	bool operator==(uint64_t const& other) const;

	const winrt::Windows::Devices::Bluetooth::BluetoothLEDevice& GetDevice() const{return Device;}
	
	void SubscribeToCharacteristic(
		winrt::impl::com_ref<winrt::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic> characteristic);
	FOnReceivedDataSignature OnDataReceived;


	void WriteCharacteristicAsync(winrt::guid characteristicUUID, const std::vector<uint8_t>& dataToWrite);
	
	winrt::weak_ref<winrt::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic> GetCharacteristic(winrt::guid characteristicUUID) const;
	
private:
	std::vector<winrt::weak_ref<winrt::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic>> Characteristics {};
	std::vector<winrt::event_token> CharacteristicTokens {};
	  
	winrt::Windows::Devices::Bluetooth::BluetoothLEDevice Device;
};
