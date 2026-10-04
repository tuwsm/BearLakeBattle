// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LimbitlessPlayerController.generated.h"

class UFlexController;
class ULimbitlessLocalPlayer;
class UInputAction;
/**
 * 
 */
UCLASS()
class LIMBITLESSBLUETOOTHPLUGIN_API ALimbitlessPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALimbitlessPlayerController();

	ULimbitlessLocalPlayer* GetLimbitlessLocalPlayer();
protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	TWeakObjectPtr<ULimbitlessLocalPlayer> LimbitlessLocalPlayer;
	TWeakObjectPtr<UFlexController> FlexController;
private:
	void SetupLimbitlessLocalPlayer();
	UFUNCTION()
	void FlexControllerConnected(UFlexController* FlexController);
	UFUNCTION()
	void OnAnalogFlex(float val);
	UFUNCTION()
	void OnDiscreteFlex(int level);
	UFUNCTION()
	void OnRotation(FVector angle);
	UFUNCTION()
	void OnAngularVelocity(FVector vel);
	UFUNCTION()
	void OnAcceleration(FVector accel);

	UPROPERTY()
	TObjectPtr<UInputAction> AnalogFlexAction;
	UPROPERTY()
	TObjectPtr<UInputAction> LightFlexAction;
	UPROPERTY()
	TObjectPtr<UInputAction> MediumFlexAction;
	UPROPERTY()
	TObjectPtr<UInputAction> StrongFlexAction;
	UPROPERTY()
	TObjectPtr<UInputAction> RotationAction;
	UPROPERTY()
	TObjectPtr<UInputAction> AngularVelocityAction;
	UPROPERTY()
	TObjectPtr<UInputAction> AccelerationAction;

};
