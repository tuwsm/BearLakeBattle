// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MuCO/CustomizableSkeletalComponent.h"
#include "CustomizablePlayerComponent.generated.h"


class IBashController;
class UPlayerData;
class ABashPlayerController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BASHCORE_API UCustomizablePlayerComponent : public UCustomizableSkeletalComponent
{
	GENERATED_BODY()

public:
	UCustomizablePlayerComponent();
	
	UFUNCTION(BlueprintCallable, Category="Customizable Player")
	virtual void LoadCustomizableInstance(UPlayerData* PlayerData);
protected:
	virtual void BeginPlay() override;
};
