// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Player/CustomizablePlayerComponent.h"
#include "MinigameCustomizablePlayerComponent.generated.h"

USTRUCT(BlueprintType)
struct FCustomizationOverride
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Override")
	FString ParameterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Override")
	FString ParameterValue;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINIGAMECORE_API UMinigameCustomizablePlayerComponent : public UCustomizablePlayerComponent
{
	GENERATED_BODY()

public:
	UCustomizableObject* GetCustomizableObject() { return CustomizableObject; }
	
	virtual void LoadCustomizableInstance(UPlayerData* PlayerData) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Override")
	TObjectPtr<UCustomizableObject> CustomizableObject;
	
	UPROPERTY(EditDefaultsOnly, Category="Override")
	TArray<FCustomizationOverride> CustomizationOverrides;
};
