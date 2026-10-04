// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LocalPlayer.h"
#include "LimbitlessLocalPlayer.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFlexControllerAssignedSignature, UFlexController*, FlexController);

UCLASS()
class LIMBITLESSBLUETOOTHPLUGIN_API ULimbitlessLocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Flex Controller")
	UFlexController* GetFlexController() const
	{
		return AssociatedController;
	}

	UFUNCTION(BlueprintCallable, Category = "Flex Controller")
	void SetFlexController(UFlexController* newController)
	{
		AssociatedController = newController;
		
		if (OnFlexControllerAssigned.IsBound())
		{
			OnFlexControllerAssigned.Broadcast(newController);
		}
	}

	FOnFlexControllerAssignedSignature OnFlexControllerAssigned;
private:
	UPROPERTY()
	TObjectPtr<UFlexController> AssociatedController {};
};
