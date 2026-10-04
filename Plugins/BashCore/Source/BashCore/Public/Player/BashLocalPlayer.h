// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/LimbitlessLocalPlayer.h"
#include "Engine/LocalPlayer.h"
#include "BashLocalPlayer.generated.h"

class UFlexController;
class UCustomizableObjectInstance;
class UCustomizableObject;

UCLASS(BlueprintType)
class BASHCORE_API UPlayerData : public UObject
{
	GENERATED_BODY()

public:
	//Player Data getters/setters
	UFUNCTION(BlueprintCallable, Category = "Player Data")
	int GetTilePos() const
	{
		return TilePos;
	}

	UFUNCTION(BlueprintCallable, Category = "Player Data")
	void SetPlayerNum(int Num)
	{
		PlayerNum = Num;
	}

	UFUNCTION(BlueprintCallable, Category = "Player Data")
	void SetTilePos(int NewTilePos)
	{
		TilePos = NewTilePos;
	}

	UFUNCTION(BlueprintCallable, Category = "Player Data")
	int GetCoins() const;

	UFUNCTION(BlueprintCallable, Category = "Player Data")
	int GetMobius() const
	{
		return Mobius;
	}

	UFUNCTION(BlueprintCallable, Category = "Player Data")
	int GetPlayerNum() const
	{
		return PlayerNum;
	}
	
	UFUNCTION(BlueprintCallable, Category = "Player Data")
	void SetCoins(int newCoins);

	UFUNCTION(BlueprintCallable, Category = "Player Data")
	void ModifyCoins(int DeltaCoins)
	{
		SetCoins(FMath::Max(Coins + DeltaCoins, 0));
	}
	UFUNCTION(BlueprintCallable, Category = "Player Data")
	void SetMobius(int newMobius)
	{
		Mobius = newMobius;
	}

	UFUNCTION(BlueprintCallable, Category = "Player Data")
	UCustomizableObjectInstance* GetCustomizableInstance() const
	{
		return CustomizableObjectInstance;
	}

	UFUNCTION(BlueprintCallable, Category = "Player Data")
	void AddBoardItem(UObject* Item);

	UFUNCTION(BlueprintCallable, Category = "Player Data")
	void RemoveBoardItem(UObject* Item);
	
	UFUNCTION(BlueprintCallable, Category = "Player Data")
	const TArray<UObject*>& GetBoardItems() const;
	
	void InitializeCustomizableInstance(UCustomizableObject* CO);

private:
	int PlayerNum = -1;
	int PlayerOrder = 0;
	int TilePos = 0;
	int Coins = 0;
	int Mobius = 0;

	UPROPERTY()
	TArray<TObjectPtr<UObject>> BoardItems{};

	UPROPERTY()
	UCustomizableObjectInstance* CustomizableObjectInstance;
};

UCLASS()
class BASHCORE_API UBashLocalPlayer : public ULimbitlessLocalPlayer
{
	GENERATED_BODY()

public:
	UBashLocalPlayer();
	
	UFUNCTION(BlueprintGetter)
	UPlayerData* GetPlayerData()
	{
		return PlayerData;
	};

	virtual void PlayerAdded(class UGameViewportClient* InViewportClient, FPlatformUserId InUserId) override;
	virtual void PlayerAdded(class UGameViewportClient* InViewportClient, int32 InControllerID) override;

protected:
	UPROPERTY(BlueprintGetter = GetPlayerData, Category = "Player Data")
	TObjectPtr<UPlayerData> PlayerData;

private:
	UPROPERTY()
	TObjectPtr<UCustomizableObject> CustomizableObject;
};
