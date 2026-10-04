// Copyright Limbitless Solutions, Inc. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MinigameUI.generated.h"

class AMinigameBase;

/**
 * 
 */
UCLASS()
class MINIGAMECORE_API UMinigameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void StartUI();

	void SetMinigame(AMinigameBase* minigame) { Minigame = minigame; }
	void SetAssignedSplit(int SplitNumber) { AssignedSplit = SplitNumber; }
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Minigame", meta = (AllowPrivateAccess = true))
	AMinigameBase* Minigame;

	UPROPERTY(BlueprintReadOnly, Category = "Minigame", meta = (AllowPrivateAccess = true))
	int AssignedSplit;
};
