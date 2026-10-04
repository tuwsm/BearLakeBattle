// Copyright Limbitless Solutions, Inc. All Rights Reserved


#pragma once
#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "ControlDisplay.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FControlDisplay
{
	GENERATED_BODY()

	// The image that will be displayed in the instructions. Use to designate what the input is (button, flex, etc.)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Display")
	UTexture2D* image{};

	// The text that will be displayed in the instructions. Describe what effect the input will have on the game or player.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Display")
	FText text{};


};
