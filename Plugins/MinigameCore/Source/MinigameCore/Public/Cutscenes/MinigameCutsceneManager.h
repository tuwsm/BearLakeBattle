// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MinigameCutsceneManager.generated.h"

DECLARE_DELEGATE(OnCutsceneCompletedSignature);

class AMinigameBase;

/**
 * Manages the behavior of minigame cutscenes when the minigame ends or completes.
 */
UCLASS(Blueprintable, BlueprintType, meta=(ShowWorldContextPin))
class MINIGAMECORE_API UMinigameCutsceneManager : public UObject
{
	GENERATED_BODY()

public:
	void StartCutscene(AMinigameBase* Minigame);
	
	OnCutsceneCompletedSignature OnCutsceneCompleted;

	bool ShouldSpawnPlayersBeforeCutscene() { return bShouldSpawnPlayers; }
protected:
	// Called by the minigame when the cutscene should begin playing
	UFUNCTION(BlueprintNativeEvent)
	void OnStartCutscene(AMinigameBase* Minigame);

	// To be called by the cutscene to end the cutscene.
	// This prompts the minigame to continue with minigame flow (e.g. starting the game or transitioning to board)
	UFUNCTION(BlueprintCallable, Category = "Cutscene")
	void EndCutscene();
	
	/* If true, players will be spawned by the minigame before the cutscene starts.
	* This can be helpful in having the cutscene transition smoothly into gameplay, but
	* isn't necessary if cutscene uses something else to represent players.
	*
	* If this cutscene is an end cutscene, players will already be spawned in their end-of-minigame state.
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Cutscene")
	bool bShouldSpawnPlayers{};

	UFUNCTION(BlueprintCallable, Category = "Cutscene")
	virtual class UWorld* GetWorld() const override;

	UPROPERTY(BlueprintReadOnly, Category = "Cutscene")
	TObjectPtr<AMinigameBase> CurrentMinigame{};
};
