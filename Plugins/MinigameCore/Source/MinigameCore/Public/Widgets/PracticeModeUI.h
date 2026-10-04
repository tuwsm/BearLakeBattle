// Copyright Limbitless Solutions, Inc. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PracticeModeUI.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMECORE_API UPracticeModeUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	class UPanelWidget* GetPreviewWindow() const;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayResetEffect();

	UFUNCTION(BlueprintImplementableEvent)
	void EndResetEffect();

	UFUNCTION(BlueprintCallable, Category = "Text")
	FVector2D GetTextSize(const class UTextBlock* Text) const;
};
