// Copyright Limbitless Solutions, Inc. All Rights Reserved


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/MinigameStanding.h"
#include "BasePointCounter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPointsChanged, int, Team, int, Amount);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINIGAMECORE_API UBasePointCounter : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBasePointCounter();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Point Counter");
	FPointsChanged OnPointsChanged;

	// Adds points to the team's point counter. In FFA, the player number is the team number.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Point Counter")
	void AddPoints(int Team, int Amount);

	// Sets a team's point counter to the amount. In FFA, the player number is the team number.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Point Counter")
	void SetPoints(int Team, int Amount);

	// Returns the current number of points of a team. In FFA, the player number is the team number.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Point Counter")
	int GetPoints(int Team) const;

	// Returns the current number of points of a player. In FFA, the player number is the team number.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Point Counter")
	int GetPointsByPlayer(int Player) const;

	// Gets the results of the minigame based on the current score
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Point Counter")
	TArray<FMinigameStanding> GetStandings() const;

	// Initializes point counter with team information
	UFUNCTION(BlueprintNativeEvent, Category = "Point Counter")
	void InitializePointCounter(int NumTeams, const TArray<int>& TeamAssignment);

	UFUNCTION(BlueprintNativeEvent, Category = "Point Counter")
	void SetupTeamAssignment(int NumTeams, const TArray<int>& TeamAssignments);
protected:
	UPROPERTY(BlueprintReadWrite, Category = "Point Info")
	TArray<int> TeamPoints{};

	// Maps player numbers to teams
	UPROPERTY(BlueprintReadWrite, Category = "Point Info")
	TArray<int> PlayersToTeams{};

private:
	bool bIsInitialized{};

public:
	UFUNCTION(BlueprintCallable, Category = "Point Counters")
	bool GetIsInitialized() const { return bIsInitialized; }
};
