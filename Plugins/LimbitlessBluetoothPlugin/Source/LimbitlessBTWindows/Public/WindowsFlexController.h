// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <winrt/base.h>

#include "CoreMinimal.h"
#include "FlexController.h"
#include "WindowsFlexController.generated.h"

class BtDeviceHolder;
/**
 * 
 */
UCLASS()
class LIMBITLESSBTWINDOWS_API UWindowsFlexController : public UFlexController
{
	GENERATED_BODY()
public:
	void Initialize(BtDeviceHolder* deviceHolder, winrt::guid writeCharacteristicUUID);

	BtDeviceHolder* GetDeviceHolder() const
	{
		return DeviceHolder;
	};

	virtual void SetScale(uint8 scale, TFunction<void()> scaleSetCallback) override;
	virtual void SetColor(EFlexColor color, TFunction<void()> colorSetCallback) override;

private:
	BtDeviceHolder* DeviceHolder;
	winrt::guid WriteCharacteristicUUID;
};
