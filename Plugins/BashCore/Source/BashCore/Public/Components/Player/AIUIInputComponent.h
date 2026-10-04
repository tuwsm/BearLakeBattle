// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIInputComponentBase.h"
#include "AIUIInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BASHCORE_API UAIUIInputComponent : public UUIInputComponentBase
{
	GENERATED_BODY()

public:
	UAIUIInputComponent();
	
	UFUNCTION(BlueprintCallable, Category = "AI UI")
	void NavigateUp();

	UFUNCTION(BlueprintCallable, Category = "AI UI")
	void NavigateDown();
	
	UFUNCTION(BlueprintCallable, Category = "AI UI")
	void NavigateLeft();
	
	UFUNCTION(BlueprintCallable, Category = "AI UI")
	void NavigateRight();
	
protected:
	virtual void InternalSetFocus(UUserWidget* widget) override;
	virtual void ClearWidgetFocus() override;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	TObjectPtr<APlayerController> FakePlayerController;
};
