// Copyright Limbitless Solutions, Inc. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BashGamemode.h"
#include "Data/ControlDisplay.h"
#include "Data/MinigameEnums.h"
#include "MinigameBase.generated.h"

// Forward declarations
class AMinigameCapture;
class UMinigameUI;
class UPracticeModeUI;
class APlayerSpawn;
class UMinigameSessionSubsystem;
class AMinigamePlayer;
class USplitscreenUI;
class UBasePointCounter;
class UMinigameCutsceneManager;
class UOverlaySlot;
class UCustomizableObjectInstance;
class UInputMappingContext;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStartedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameEndedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameResetSignature);

UCLASS()
class MINIGAMECORE_API AMinigameBase : public ABashGamemode
{
	GENERATED_BODY()

public:
	AMinigameBase();

	/*
	 *  Game flow
	 */
	
	// Readies a Player to exit practice mode
	UFUNCTION(BlueprintCallable, Category = "Minigame|Practice")
	void ReadyPlayer(int Player, bool state);

	// Checks the ready status of a player in practice mode
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Minigame|Practice")
	int CheckReady(int Player) const;

	UFUNCTION(BlueprintGetter)
	int32 GetMinigameNumPlayers() { return NumPlayers; }
	
	// Ends the minigame early
	UFUNCTION(BlueprintCallable, Category = "Minigame")
	void EndGame();

	UFUNCTION(BlueprintGetter)
	double GetTimeRemaining() const { return TimeRemaining; }

	UFUNCTION(BlueprintSetter)
	void SetTimeRemaining(double time) { TimeRemaining = time; }

	UFUNCTION(BlueprintGetter)
	double GetTimeElapsed() const { return TimeElapsed; }

	UFUNCTION(BlueprintGetter)
	bool IsPractice() const { return bIsPractice; }

	UFUNCTION(BlueprintGetter)
	bool IsInProgress() const { return bIsInProgress; }

	UFUNCTION(BlueprintCallable, Category = "Minigame|Points")
	UBasePointCounter* GetPointCounter() const { return PointCounter; }
	
	
	/*
	 *  Players & Teams
	 */
	
	UFUNCTION(BlueprintCallable, Category = "Minigame|Player")
	AMinigamePlayer* GetPlayer(int PlayerNum) const;

	UFUNCTION(BlueprintCallable, Category = "Minigame|Player")
	const TArray<AMinigamePlayer*>& GetPlayers() const { return Players; }

	UFUNCTION(BlueprintGetter)
	EMinigameType GetTeamType() const { return TeamType; }

	/*
	 *  Customization overrides
	 */
	
	UCustomizableObjectInstance* GetCachedOverride(int32 PlayerNumber);
	void CacheOverride(UCustomizableObjectInstance* Override, int32 PlayerNumber);

	/*
	 *  Cameras/UI
	 */

	// Registers a camera to be used by the splitscreen system
	UFUNCTION(BlueprintCallable, Category = "Minigame|Splitscreen")
	void AddCamera(AMinigameCapture* Camera, int CameraNumber);

	// Gets the camera assigned to this player through the splitscreen system
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Minigame|Splitscreen")
	AMinigameCapture* GetCamera(int PlayerNumber) const;

	// Returns the number of camera splits this gamemode should have
	UFUNCTION(BlueprintCallable, Category = "Minigame|Splitscreen")
	int GetNumCameraSplits() const;
	
	UFUNCTION(BlueprintCallable, Category = "MinigameUI")
	USplitscreenUI* GetMinigameWidgetRoot() const { return CurrentMinigameUI; }

	UFUNCTION(BlueprintCallable, Category = "MinigameUI")
	UOverlaySlot* AddWidgetToMinigameUISplit(UUserWidget* InWidget, int Split);
	
	UFUNCTION(BlueprintCallable, Category = "MinigameUI")
	void PlayMinigameTransitionEffects();
	
protected:
	/*
	 *  Base overrides
	 */
	virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;
	
	virtual void Tick(float DeltaTime) override;

	virtual void StartPlay() override;
	
	virtual void ResetLevel() override;


	/*
	 *  Events
	 */
public:
	// Called after players are spawned and the minigame base has initialized. Also called after every reset
	UPROPERTY(BlueprintAssignable);
	FGameStartedSignature OnMinigameStartEvent;

	// Triggered when the minigame end has been initialized, either from the timer or explicit call of EndGame()
	UPROPERTY(BlueprintAssignable)
	FGameEndedSignature OnMinigameEndEvent;

	// Triggered right before the minigame is reset. Use this to clean up persistent state
	UPROPERTY(BlueprintAssignable)
	FGameResetSignature OnMinigameResetEvent;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnMinigameStart();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnMinigameEnd();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnMinigameReset();

private:
	/*
	 *  Properties
	 */

	/*
	 *  General Settings 
	 */
	
	// The Pawns to spawn as the players of each team. Index 0 corresponds to the first team, etc.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Minigame|Settings", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<AMinigamePlayer>> PlayerObjects;

	// The team arrangement of this minigame.
	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetTeamType, Category = "Minigame|Settings")
	EMinigameType TeamType;

	// The amount of time the minigame should last before ending, in seconds
	UPROPERTY(EditDefaultsOnly, Category = "Minigame|Settings")
	double MinigameDuration;
	
	/*
	 *  Practice Mode
	 */
	
	// The name of the minigame to display in Practice UI
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Minigame|Practice", meta = (AllowPrivateAccess = true))
	FString MinigameName;

	// The description of the minigame. This should explain what the goal of the minigame is and how to play
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Minigame|Practice", meta = (AllowPrivateAccess = true))
	FString Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Minigame|Practice", meta = (AllowPrivateAccess = true))
	TArray<FControlDisplay> Controls;

	// Amount of time between game ending and game resetting in practice mode
	UPROPERTY(EditDefaultsOnly, Category = "Minigame|Practice")
	float ResetDelay{ 1.f };


	/*
	 *  UI
	 */
	
	// The UI to spawn during the Practice phase
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Minigame|UI", meta = (AllowPrivateAccess = true))
	TSubclassOf<UPracticeModeUI> PracticeUIClass;

	// The UI to display in the minigame. Can be left unassigned if no minigame UI is desired
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Minigame|UI", meta = (AllowPrivateAccess = true))
	TSubclassOf<UMinigameUI> MinigameUIClass;

	// Should splits be assigned to each player or to each team?
	UPROPERTY(EditDefaultsOnly, Category = "Minigame|Splitscreen")
	ESplitBy SplitBy;

	// Whether this minigame should use splitscreen
	UPROPERTY(EditDefaultsOnly, Category = "Minigame|Splitscreen", meta = (AllowPrivateAccess = true))
	bool bUseSplitscreen;

	// Widget classes to spawn for specified number of splits
	UPROPERTY(EditDefaultsOnly, Category = "Minigame|Splitscreen", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<USplitscreenUI>> SplitscreenUIClasses;

	/*
	 *  Gameplay
	 */
	
	// The amount of time that has passed since the start of the minigame, in seconds
	UPROPERTY(VisibleInstanceOnly, BlueprintGetter = GetTimeElapsed, Category = "Minigame|Gameplay")
	double TimeElapsed;

	// Number of players currently in this game
	UPROPERTY(BlueprintGetter = GetMinigameNumPlayers, meta = (AllowPrivateAccess = true), Category = "Minigame|Gameplay")
	int NumPlayers;

	// True if the minigame is in practice mode
	UPROPERTY(BlueprintGetter = IsPractice, meta = (AllowPrivateAccess = true), Category = "Minigame|Gameplay")
	bool bIsPractice;

	// True if the minigame is not finished
	UPROPERTY(BlueprintGetter = IsInProgress, meta = (AllowPrivateAccess = true), Category = "Minigame|Gameplay")
	bool bIsInProgress;

	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bDebugHideUI{};

	// The amount of time remaining for this minigame, in seconds.
	UPROPERTY(EditInstanceOnly, BlueprintGetter = GetTimeRemaining, BlueprintSetter = SetTimeRemaining, Category = "Minigame|Gameplay", meta = (AllowPrivateAccess = true))
	double TimeRemaining;
	
	/*
	 *  Cutscenes
	 */
	UPROPERTY(EditDefaultsOnly, Category="Minigame|Cutscenes")
	TSubclassOf<UMinigameCutsceneManager> IntroCutscene{};

	UPROPERTY(EditDefaultsOnly, Category="Minigame|Cutscenes")
	TSubclassOf<UMinigameCutsceneManager> EndingCutscene{};


	/*
	 *  Private references 
	 */
	
	TObjectPtr<UMinigameSessionSubsystem> MinigameSessionSubsystem;
	TObjectPtr<UBasePointCounter> PointCounter{};

	TObjectPtr<UInputMappingContext> MinigameMappingContext{};


	TObjectPtr<UPracticeModeUI> PracticeUI{};
	TObjectPtr<USplitscreenUI> CurrentMinigameUI{};
	UPROPERTY()
	TObjectPtr<UMinigameCutsceneManager> CurrentCutscene{};

	UPROPERTY()
	TArray<TObjectPtr<UCustomizableObjectInstance>> CachedCustomizationOverrides;

	// Index: Player | Value: Team of player
	TArray<TArray<int>> Teams;
	TArray<int> TeamsByPlayers;
	TArray<bool> ReadyPlayers;

	TArray<TObjectPtr<AMinigamePlayer>> Players{};

	// Player spawns by player count, team, and position
	APlayerSpawn* PlayerSpawns[4][2][4];

	TArray<AMinigameCapture*> SplitCameras;
	
	TObjectPtr<ACameraActor> DefaultCamera;

	FTimerHandle ResetTimerHandle{};

	// Returns the index in playerSpawns that has the specified team and position
	AActor* GetPlayerSpawn(int Team, int Pos) const;
	void SpawnPlayers();

	// Splits players into teams depending on the Team Type selected.
	// Index of resultant array is the player number, value is the team number
	TArray<int> SplitIntoTeams();
	TArray<TArray<int>> OrganizeByTeams(TArray<int> TeamsByPlayers);

	// Initializes the team points array based on team arrangement.
	void InitPoints();

	UFUNCTION()
	void SetupGame();

	UFUNCTION()
	void StartGame();

	// Finds and stores references to minigame cameras in the level
	void FindMinigameCameras();

	// Ends the game and starts transition back to board, playing any end cutscenes
	void ProcessMinigameEnd();

	void ChangeLevel();

	// Ends practice and begins transition to actual minigame
	void EndPracticeMode();

	void FindPlayerSpawns();
	
	void ClearMinigameUI();

	// Draws minigame UI whenever the minigame is started.
	void DrawMinigameUI();

	// Resets the game
	void StartReset();

	USplitscreenUI* SpawnSplitscreenUI(int NumSplits);
	void SetupMinigameUI(USplitscreenUI* SplitscreenUI);

	void EnablePlayerInput();
	void DisablePlayerInput();
	
	/**
	*	Handles ending of the game.
	*	@param bTransitionToPractice True if the game will transition
	*	@param bOverrideIfInProgress Can end the game, even if the game is already ending. Used to transition
	*	out of practice mode if practice mode is already resetting
	*/
	void EndGameInternal(bool bTransitionToPractice, bool bOverrideIfInProgress = false);
	
	// Alerts to log and error
	FORCEINLINE void AlertWarning(const FString& Text) const;
	FORCEINLINE void AlertError(const FString& Text) const;
};

