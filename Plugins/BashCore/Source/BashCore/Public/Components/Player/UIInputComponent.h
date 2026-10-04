// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIInputComponentBase.h"
#include "UIInputComponent.generated.h"

class IBashController;
class UWidget;
class UMenu;
class ABashPlayerController;
class UInputMappingContext;
class UInputAction;
class UInputAction;
class UUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASHCORE_API UUIInputComponent : public UUIInputComponentBase
{
	GENERATED_BODY()

public:
	UUIInputComponent();
	
	//setups up input mapping context and bindings.
	virtual void SetupInput(ABashPlayerController* owner);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	virtual void InternalSetFocus(UUserWidget* widget) override;
	
	//Input:
	//Input Actions:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> SelectAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> BackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> StartAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> DownNavigateAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> UpNavigateAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> LeftNavigateAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> RightNavigateAction;
	//Input Mapping context:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> MenuMappingContext;

	// How long should the input be pressed to start hold navigating
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float InitialHoldNavigationDelay = .75;

	// How often should navigation happen when hold navigating
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float RepeatHoldNavigationDelay = .25;
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION()
	void NavigateUp();
	UFUNCTION()
	void NavigateDown();
	UFUNCTION()
	void NavigateLeft();
	UFUNCTION()
	void NavigateRight();
	UFUNCTION()
	void OnUpHeld();
	UFUNCTION()
	void OnDownHeld();
	UFUNCTION()
	void OnLeftHeld();
	UFUNCTION()
	void OnRightHeld();
	UFUNCTION()
	void OnUpCompleted();
	UFUNCTION()
	void OnDownCompleted();
	UFUNCTION()
	void OnLeftCompleted();
	UFUNCTION()
	void OnRightCompleted();
	UFUNCTION()
	void StartButtonPressed();
	UFUNCTION()
	void BackButtonPressed();
	
	void SetHoldDirection(ENavigationDirection direction);
	virtual void ClearWidgetFocus() override;
	void OnDirectionReleased(ENavigationDirection direction);
	
	float CurrentHeldNavDelay{};
	ENavigationDirection HeldNavDirection{};
private:
	UPROPERTY()
	TObjectPtr<ABashPlayerController> OwningPlayerController;
};
