// Copyright Limbitless Solutions, Inc. All Rights Reserved

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMinigameType : uint8
{
	MT_FFA	UMETA(DisplayName = "Free for All"),
	MT_3v1	UMETA(DisplayName = "3v1"),
	MT_2v2	UMETA(DisplayName = "2v2"),
};

UENUM(BlueprintType)
enum class ESplitBy : uint8
{
	PLAYERS	UMETA(DisplayName = "Players"),
	TEAMS	UMETA(DisplayName = "Teams"),
};
