// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MinigameCutsceneManager.h"
#include "LevelSequenceMinigameCutsceneManager.generated.h"

class ALevelSequenceActor;
class ULevelSequence;
/**
 * A minigame cutscene that uses a level sequence. The level sequence should have Possessable bindings (Player0, Player1, etc.)
 */
UCLASS()
class MINIGAMECORE_API ULevelSequenceMinigameCutsceneManager : public UMinigameCutsceneManager
{
	GENERATED_BODY()

	ULevelSequenceMinigameCutsceneManager();

public:
	virtual void OnStartCutscene_Implementation(AMinigameBase* Minigame) override;

	// Initializes level sequence actor
	// By default, binds the first minigame capture to the "Camera" binding tag
	// If bBindSpawnedPlayersToSequence is true, spawned players are bound to binding tags "Player0", "Player1", "Player2", and "Player3" 
	UFUNCTION(BlueprintNativeEvent)
	void InitializeLevelSequence(ALevelSequenceActor* SequenceActor);

	// Called when the level sequence is finished
	UFUNCTION(BlueprintNativeEvent)
	void OnLevelSequenceComplete();
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Cutscene")
	TObjectPtr<ULevelSequence> LevelSequence{};

	// If this is true and bShouldSpawnPlayers, the spawned players will be bound to the level sequence
	UPROPERTY(EditDefaultsOnly, Category = "Cutscene")
	bool bBindSpawnedPlayersToSequence{};
};
