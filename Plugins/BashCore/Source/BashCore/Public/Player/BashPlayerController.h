// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BashController.h"
#include "BaseClasses/LimbitlessPlayerController.h"
#include "Components/Player/UIInputComponent.h"
#include "GameFramework/PlayerController.h"
#include "BashPlayerController.generated.h"


class UBashLocalPlayer;
class UUIInputComponent;

UCLASS()
class BASHCORE_API ABashPlayerController : public ALimbitlessPlayerController, public IBashController
{
	GENERATED_BODY()
public:
	ABashPlayerController();

	UFUNCTION()
	virtual UUIInputComponentBase* GetUiInputComponent() const override;

	UUIInputComponent* GetPlayerUiInputComponent() const;

	UFUNCTION()
	virtual UPlayerData* GetPlayerData() const override;

	UFUNCTION()
	virtual APawn* GetPlayerPawn() const override;
	
	UFUNCTION(BlueprintCallable, Category = "Local Player")
	UBashLocalPlayer* GetBashLocalPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UUIInputComponent> UIInputComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Local Player")
	TObjectPtr<UBashLocalPlayer> BashLocalPlayer;
private:
	void SetupBashLocalPlayer();

};
