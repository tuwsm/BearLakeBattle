// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BashLocalPlayer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AIPlayerDataSubsystem.generated.h"

class UCustomizableObject;

UCLASS()
class BASHCORE_API UAIPlayerDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UAIPlayerDataSubsystem();
	
	UPlayerData* GetAIPlayerData(int32 Index);

private:
	UPROPERTY()
	TArray<UPlayerData*> PlayerData;

	UPROPERTY()
	TObjectPtr<UCustomizableObject> CustomizableObject;
};