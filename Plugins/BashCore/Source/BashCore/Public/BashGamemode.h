// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BashGamemode.generated.h"

class UCircularWipeWidget;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FLoadLevelParams
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category="LoadLevel")
	FName LevelToOpenName;

	UPROPERTY(BlueprintReadWrite, Category="LoadLevel")
	TSoftObjectPtr<UWorld> LevelToOpen;
};

UCLASS()
class BASHCORE_API ABashGamemode : public AGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="LoadLevel")
	void TransitionToLevel(FLoadLevelParams loadLevelParams);
	
protected:
	virtual void BeginPlay() override;

	//Called after the circular wipe
	UFUNCTION()
	virtual void OnEnterTransitionFinish();

	UFUNCTION()
	void PlayTransitionEffects();

protected:
	UPROPERTY(EditAnywhere, Category = "BashGamemode")
	TSubclassOf<UCircularWipeWidget> CircularWipeClass;

	UPROPERTY( BlueprintReadOnly, Category = "BashGamemode")
	TObjectPtr<UCircularWipeWidget> CircularWipeWidget;

private:
	UFUNCTION()
	void OpenLevel();

private:
	FLoadLevelParams LevelToLoadParams;
};
