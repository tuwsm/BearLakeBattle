// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MinigameAIController.generated.h"

class AMinigamePlayer;
class AMinigameBase;

UCLASS()
class MINIGAMECORE_API AMinigameAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMinigameAIController();

	virtual void OnPossess(APawn* InPawn) final override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnMinigamePlayerPossessed();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Minigame")
	TObjectPtr<AMinigameBase> Minigame;

	UPROPERTY(BlueprintReadOnly, Category = "Minigame")
	TObjectPtr<AMinigamePlayer> Player;
};
