// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BashCoreBlueprintLibrary.generated.h"

class UPlayerData;

UCLASS()
class BASHCORE_API UBashCoreBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Bash Core", meta=(WorldContext="WorldContextObject"))
	static UPlayerData* GetPlayerData(const UObject* WorldContextObject, int32 PlayerIndex);
};
