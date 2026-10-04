// Copyright Limbitless Solutions, Inc. All Rights Reserved

#pragma once

#include "MinigameStanding.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FMinigameStanding
{
	GENERATED_BODY()

	// Number of the player in this standing
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Standing")
	int Player{};

	// 1st place, 2nd place, etc. Multiple players can have the same place
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Standing")
	int Place{};
};
