// Copyright Limbitless Solutions, Inc. All Rights Reserved


#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Data/MinigameStanding.h"
#include "MinigameSessionSubsystem.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(int, FGetMinigamePlayerCountSignature);

/**
 * 
 */
UCLASS()
class MINIGAMECORE_API UMinigameSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Minigame Output")
	TArray<FMinigameStanding> GetMinigameResults() const { return MinigameResults; }

	void SetMinigameResults(const TArray<FMinigameStanding>& Results) { MinigameResults = Results; }

	UFUNCTION(BlueprintCallable, Category = "Minigame Input")
	void SetPlayerCount(int PlayerCount) { NumMinigamePlayers = PlayerCount; }

	UFUNCTION(BlueprintCallable, Category = "Minigame Input")
	int GetPlayerCount() const { return NumMinigamePlayers; }
	
	// Sets the level to return to after the minigame
	UFUNCTION(BlueprintCallable, Category = "Minigame Input")
	void SetMinigameReturnLevel(TSoftObjectPtr<UWorld> Level) { MinigameReturnLevel = Level; };

	UFUNCTION(BlueprintCallable, Category = "Minigame Input")
	TSoftObjectPtr<UWorld> GetMinigameReturnLevel() const { return MinigameReturnLevel; }
private:
	int NumMinigamePlayers;
	
	TArray<FMinigameStanding> MinigameResults;

	TSoftObjectPtr<UWorld> MinigameReturnLevel;
};

