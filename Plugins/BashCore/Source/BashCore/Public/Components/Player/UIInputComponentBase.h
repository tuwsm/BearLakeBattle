// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Components/ActorComponent.h"
#include "UIInputComponentBase.generated.h"

class UWidget;
class UMenu;
class IBashController;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIInputSignature, TScriptInterface<IBashController>, FromPlayer);

/* Used to retain a stack of open menus. Allows the closing and opening of menus and returning to the previous location.
 * Menu is the actual menu widget. SelectedWidget is the last selected widget before exiting that menu.
 */
UCLASS()
class UMenuStackContext : public UObject
{
	GENERATED_BODY()

public:
	void SetMenu(UMenu* menu);

	UMenu* GetMenu() const;
	void SetSelectedWidget(UUserWidget* widget);
	UUserWidget* GetSelectedWidget() const;

protected:
	TWeakObjectPtr<UMenu> Menu;
	TWeakObjectPtr<UUserWidget> SelectedWidget;
	
};


UCLASS(Abstract)
class BASHCORE_API UUIInputComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UUIInputComponentBase();

	/* Call to open a menu with this player as the controller.
	 * @param menu - The menu to open
	 * @param clearMenuStack - if true clears all menus from the menu stack. Used if previous menus will not be accesible.
	 */
	UFUNCTION(BlueprintCallable, Category = "Events")
	virtual void OpenMenu(UMenu* menu, bool clearMenuStack);
	virtual void ClearWidgetFocus() {};

	/* Call to close a menu. Will close all menus on top of it.
	 * @param menu - The menu to close
	 */
	UFUNCTION(BlueprintCallable, Category = "Events")
	virtual void CloseMenu(UMenu* menu, bool closeAll = false);

	UFUNCTION(BlueprintCallable, Category = "Events")
	virtual void CloseAllMenus();
	
	//Has User focus specific widget.
	UFUNCTION(BlueprintCallable, Category = "Events")
	virtual void FocusWidget(UUserWidget* widget);
	
	UFUNCTION(BlueprintCallable, Category = "Events")
	UWidget* GetFocusWidget() const { return FocusedWidget; }

	UFUNCTION(BlueprintCallable, Category = "Events")
	void SelectOption();
	
	//Input Delegates
	UPROPERTY(BlueprintAssignable, Category = "Input")
	FUIInputSignature OnSelectButtonPressed;
	UPROPERTY(BlueprintAssignable, Category = "Input")
	FUIInputSignature OnBackButtonPressed;
	UPROPERTY(BlueprintAssignable, Category = "Input")
	FUIInputSignature OnStartButtonPressed;
	UPROPERTY(BlueprintAssignable, Category = "Input")
	FUIInputSignature OnUpButtonPressed;
	UPROPERTY(BlueprintAssignable, Category = "Input")
	FUIInputSignature OnDownButtonPressed;
	UPROPERTY(BlueprintAssignable, Category = "Input")
	FUIInputSignature OnLeftButtonPressed;
	UPROPERTY(BlueprintAssignable, Category = "Input")
	FUIInputSignature OnRightButtonPressed;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FUIInputSignature OnUpButtonHeld;
	UPROPERTY(BlueprintAssignable, Category = "Input")
	FUIInputSignature OnDownButtonHeld;
	UPROPERTY(BlueprintAssignable, Category = "Input")
	FUIInputSignature OnLeftButtonHeld;
	UPROPERTY(BlueprintAssignable, Category = "Input")
	FUIInputSignature OnRightButtonHeld;
	
protected:
	virtual void InternalSetFocus(UUserWidget* widget) {};
	
	enum class ENavigationDirection
	{
		END_None,
		END_Up,
		END_Down,
		END_Left,
		END_Right
	};
	
	void NavigateDirection(ENavigationDirection direction);

	UPROPERTY()
	TObjectPtr<UWidget> FocusedWidget{};
	
	UPROPERTY()
	TScriptInterface<IBashController> OwningPlayer;

	UPROPERTY()
	TArray<UMenuStackContext*> MenuStack;
};
