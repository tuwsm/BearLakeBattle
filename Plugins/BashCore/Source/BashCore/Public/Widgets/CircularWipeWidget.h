// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CircularWipeWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_DELEGATE(FOnWipeFilledSignature);

USTRUCT(BlueprintType)
struct FCircleWipeParams
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Wipe Params")
	FOnWipeFilledSignature onWipeFilled;
	UPROPERTY(BlueprintReadOnly, Category = "Wipe Params")
	FOnWipeFilledSignature onWipeComplete;

};

UCLASS()
class BASHCORE_API UCircularWipeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Wipe Control")
	void StartWipe(FCircleWipeParams params);

	UFUNCTION(BlueprintCallable, Category = "Wipe Control")
	void FadeFromBlack(FCircleWipeParams params);

	UFUNCTION(BlueprintCallable, Category = "Wipe Control")
	void PlayFullWipe(FCircleWipeParams params);
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Wipe Control")
	void StartWipeVisuals(FCircleWipeParams params);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Wipe Control")
	void EndWipeVisuals(FCircleWipeParams params);

	UFUNCTION(BlueprintImplementableEvent, Category = "Wipe Control")
	void PlayFullWipeVisuals(FCircleWipeParams params);

	UFUNCTION(BlueprintCallable, Category = "Wipe Control")
	void CallDelegate(FOnWipeFilledSignature delegate);
};
