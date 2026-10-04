// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectableWidget.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class USelectableWidget : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BASHCORE_API ISelectableWidget
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//calling on selected will call cpp and blueprint version. Anything that the UI Controller can focus and interact with should either implement this or be a widget button.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Selection")
	void OnSelected();
};
