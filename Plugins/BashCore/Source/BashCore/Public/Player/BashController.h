// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BashController.generated.h"

class UUIInputComponentBase;
class UPlayerData;

UINTERFACE(NotBlueprintable, BlueprintType)
class UBashController : public UInterface
{
	GENERATED_BODY()
};

class BASHCORE_API IBashController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Bash Controller")
	virtual UUIInputComponentBase* GetUiInputComponent() const { return nullptr; }

	UFUNCTION(BlueprintCallable, Category = "Bash Controller")
	virtual UPlayerData* GetPlayerData() const { return nullptr; }

	UFUNCTION(BlueprintCallable, Category = "Bash Controller")
	virtual APawn* GetPlayerPawn() const { return nullptr; }
};
