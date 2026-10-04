// Copyright Limbitless Solutions, Inc. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MinigamePlayer.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class AMinigameBase;

UCLASS()
class MINIGAMECORE_API AMinigamePlayer : public APawn
{
	GENERATED_BODY()

public:
	AMinigamePlayer();

	UPROPERTY(BlueprintReadOnly, Category = "Minigame Player")
	int Team{};

	UPROPERTY(BlueprintReadOnly, Category = "Minigame Player")
	int PlayerNumber{};

	UPROPERTY(BlueprintReadOnly, Category = "Minigame Player")
	bool bHasFlexDevice{};

	UPROPERTY(BlueprintReadOnly, Category = "Minigame Player")
	bool bIsReady{};
	
	UFUNCTION()
	void ReadyPlayer(const FInputActionValue& value);

	UPROPERTY(BlueprintReadOnly, Category = "Minigame Player")
	AMinigameBase* Minigame;
	
	// Called when the minigame creates the player. This happens before OnMinigameStart is called
	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerSpawned();

private:
	TObjectPtr<UInputAction> ReadyAction;

	// Disables debug input mapping contexts from applying to players.
	// In non-editor builds, debug inputs are always disabled
	UPROPERTY(EditDefaultsOnly, Category = "Debug")
	bool bDisableDebugInputs{};
	
#if WITH_EDITOR
	TObjectPtr<UInputMappingContext> DebugInputMapping;
	TObjectPtr<UInputAction> ReadyAllPlayersAction;

	TObjectPtr<UInputAction> SetPlayerCount1;
	TObjectPtr<UInputAction> SetPlayerCount2;
	TObjectPtr<UInputAction> SetPlayerCount3;
	TObjectPtr<UInputAction> SetPlayerCount4;

	void ReadyAllPlayers();

	void SetPlayerCountOne()	{ SetPlayerCount(1); }
	void SetPlayerCountTwo()	{ SetPlayerCount(2); }
	void SetPlayerCountThree()	{ SetPlayerCount(3); }
	void SetPlayerCountFour()	{ SetPlayerCount(4); }
	
	void SetPlayerCount(int32 PlayerCount) const;
#endif
	
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* playerInputComponent) override;
};
