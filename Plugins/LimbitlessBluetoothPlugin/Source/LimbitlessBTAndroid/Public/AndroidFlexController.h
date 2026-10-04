// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlexController.h"
#include "Interface/BLEManagerInterface.h"
#include "AndroidFlexController.generated.h"


class IBLEDeviceInterface;
/**
 * 
 */
UCLASS()
class LIMBITLESSBTANDROID_API UAndroidFlexController : public UFlexController
{
	GENERATED_BODY()
public:
	void SubscribeToDeviceNotification(FString characteristicUUID, const FOnServiceSetDelegate& onFirstNotification);
	void SubscribeToDeviceNotification(const FOnServiceSetDelegate& onFirstNotification);
	void Initialize(TScriptInterface<IBLEDeviceInterface> deviceHolder, FString characteristicUUID);
	
	virtual void SetColor(EFlexColor color, TFunction<void()> colorSetCallback) override;
	virtual void SetScale(uint8 scale, TFunction<void()> scaleSetCallback) override;

	TScriptInterface<IBLEDeviceInterface> GetDevice() const
	{
		return DeviceHolder;	
	}
	
private:
	TScriptInterface<IBLEDeviceInterface> DeviceHolder;
	FString CharacteristicUUID;

	bool bHasReceivedFirstNotif{};
};
