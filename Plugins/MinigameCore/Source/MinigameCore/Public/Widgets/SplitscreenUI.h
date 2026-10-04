// Copyright Limbitless Solutions, Inc. All Rights Reserved

#pragma once

//#include <Components/CanvasPanel.h>

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Math/MathFwd.h"
#include "SplitscreenUI.generated.h"

class UCanvasPanel;
/**
 * 
 */
UCLASS(BlueprintType)
class MINIGAMECORE_API USplitscreenUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Splitscreen")
	int GetNumSplits() const;
	
	UFUNCTION(BlueprintCallable, Category = "Splitscreen")
	class UOverlay* GetSplitPanel(int Num) const;

	UFUNCTION(BlueprintImplementableEvent)
	UCanvasPanel* GetRootCanvas() const;
	
	void NativeOnInitialized() override;

private:

	UPROPERTY(BlueprintReadWrite, Category = "Splits", meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<UOverlay>> Splits{};

	UPROPERTY(EditDefaultsOnly, Category = "Splits")
	TArray<TObjectPtr<class UCanvasRenderTarget2D>> RenderTargets{};

	UPROPERTY(EditDefaultsOnly, Category = "Splits")
	FVector2D TargetSize{};
};
