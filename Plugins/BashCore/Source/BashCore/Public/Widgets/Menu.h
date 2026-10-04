// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player/BashController.h"
#include "Menu.generated.h"

class IBashController;
class ABashPlayerController;

UCLASS()
class BASHCORE_API UMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UMenu(const FObjectInitializer& ObjectInitializer);

	/*  Call to open the menu. Calls the bp function as well.
	 *  This is specifically for visuals. For Menu Functionality(IE. Subscribing to events), refer to @OnEnterMenu()
	 */
	virtual void OnOpenMenu(TScriptInterface<IBashController> owningPlayer);
	UFUNCTION(BlueprintImplementableEvent, Category = "Menu Events")
	void OnOpenMenuBP();
	
	/*  Called to close the menu. Resets the state of OwningPlayer to null, so be sure to call the super after using it. Calls the bp function as well.
	 *  Specifically to visually close the menu. For Menu Functionality (IE. Unsubscribing from events) refer to @OnExitMenu()
	 */
	virtual void OnCloseMenu();
	UFUNCTION(BlueprintImplementableEvent, Category = "Menu Events")
	void OnCloseMenuBP();

	/*  On Enter Menu is called when this menu becomes a player's active menu.
	 *	This is separate from a visual opening because when returning from a pop up menu, the original menu would still be visible.
	 *	Use to enable menu functionality(IE. Subscribing to events.)
	 */
	virtual void OnEnterMenu(TScriptInterface<IBashController> owningPlayer);
	UFUNCTION(BlueprintImplementableEvent, Category = "Menu Events")
	void OnEnterMenuBP();

	/* On Exit Menu is called when this menu is no longer a player's active menu. 
	 * When Opening a pop up menu, this menu will still exist but is not interactable.
	 * Use to disable functionality(IE. Unsubscribing from events.)
	 */
	virtual void OnExitMenu(TScriptInterface<IBashController> owningPlayer);
	UFUNCTION(BlueprintImplementableEvent, Category = "Menu Events")
	void OnExitMenuBP();

	
	UFUNCTION(BlueprintCallable, Category = "Menu")
	UUserWidget* GetDefaultSelectedWidget() const
	{
		return DefaultSelectedWidget;
	};

	UFUNCTION(BlueprintCallable, Category = "Menu")
	bool AllowsHoldNavigation() const
	{
		return bAllowHoldNavigation;
	};
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu", meta = (ExposeOnSpawn = "true"))
	UUserWidget* DefaultSelectedWidget;
	
	UPROPERTY(BlueprintReadOnly, Category = "Menu")
	TScriptInterface<IBashController> OwningPlayer;

	// If true, this menu will quickly navigable by holding directional inputs. Best for longer menus
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
	bool bAllowHoldNavigation{};
};
