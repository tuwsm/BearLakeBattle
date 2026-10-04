// Copyright Limbitless Solutions, Inc. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerRotationComponent.generated.h"

class UInputAction;
class UEnhancedInputLocalPlayerSubsystem;

/**
 * Processes raw rotation input data to provide helpful utilities.
 * Recommended if minigame needs motion inputs for gameplay.
 * Requires resetting the initial orientation for accurate Z-axis orientation
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINIGAMECORE_API UPlayerRotationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerRotationComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
						   FActorComponentTickFunction* ThisTickFunction) override;
	
	public:
	/* The initial position of the crosshair.
	*  Each coordinate is a percentage of the screen size away from the top left corner
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Rotation")
	FVector2D InitialPosition{ .5, .5 };
	
	// Sets the initial rotation to the current rotation. Helpful to reset effects of drift along Z-axis
	UFUNCTION(BlueprintCallable, Category = "Player Rotation")
	virtual void ResetInitialOrientation();

	// Returns the rotation from the set initial orientation
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player Rotation")
	virtual FQuat GetDeltaRotation() const { return DeltaRot; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player Rotation")
	FVector GetDeltaRotationEuler() const { return GetDeltaRotation().Euler(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player Rotation")
	FRotator GetDeltaRotator() const { return GetDeltaRotation().Rotator(); }

	// Gets the screenspace position of the aimed position. Good for rendering a crosshair on a widget.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player Rotation")
	virtual FVector2D GetAimPosition() const { return AimPos; }

	// Gets a direction from the camera to the aimed position in global worldspace. Good for raycasting to where a crosshair is visually aiming.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player Rotation")
	virtual FVector GetDirectionFromCamera(FQuat CameraOrientation) const;

	UFUNCTION(BlueprintCallable, Category = "Aiming")
	virtual void AddAimOffset(const FVector2D& DeltaOffset) { AimOffset += DeltaOffset; }
	
	UFUNCTION(BlueprintCallable, Category = "Aiming")
	virtual void SetAimOffset(const FVector2D& NewAimOffset) { AimOffset = NewAimOffset; }
	
	// Reads the rotation value from the Rotation input action
	UFUNCTION(BlueprintCallable, Category = "Player Rotation")
	FQuat GetRotationInputValue() const;

	UFUNCTION(BlueprintCallable, Category = "Player Rotation")
	FVector GetRotationInputValueVector() const;

	// Returns the resolution used for rotation aiming
	UFUNCTION(BlueprintCallable, Category = "Player Rotation")
	FVector2D GetSetScreenResolution() const { return ScreenResolution; };
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> RotationAction;

	virtual void InitializeComponent() override;

	// Updates AimPos from rotation, usually the delta rotation
	void UpdateAimPosition(const FQuat& Rotation);

protected:
	void UpdateDeltaRotation()
	{
		DeltaRot = GetRotationInputValue() * InitialRotation.Inverse();
	}
	
	FVector GetRotationInputValueVectorRaw() const;
	
	// Screen distance traveled per angle of rotation
	UPROPERTY(EditDefaultsOnly, Category = "Player Rotation")
	double AimSensitivity{ 25.0 };

	UPROPERTY(EditDefaultsOnly, Category = "Player Rotation")
	FVector2D ScreenResolution{ 1920, 1080 };

	// The distance from the edge of the screen that the aimed position must remain in
	UPROPERTY(EditDefaultsOnly, Category = "Player Rotation")
	double ClampOffset;
	
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem;
	
	FVector2D AimPos{};
	FVector2D AimOffset{};

	// The rotation as read by the flex controller to consider as identity
	FQuat InitialRotation{ FQuat::Identity };

	// The rotation from the initial rotation to the current flex controller rotation
	FQuat DeltaRot{};

	float YawOffset{};
	
	FVector2D SquareResolution{ScreenResolution.X, ScreenResolution.X};

	FVector2D ClampVector(FVector2D In, FVector2D Max, double Offset);
	
};
