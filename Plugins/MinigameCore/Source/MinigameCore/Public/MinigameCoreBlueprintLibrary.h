// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MinigameCoreBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMECORE_API UMinigameCoreBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Gets the angle off the XY plane (pitch) needed to shoot a freefall projectile from Source to Target given a launch speed.
	 * A trajectory may not exist if LaunchSpeed is too low for the given GravityAcceleration and source-to-target distance.
	 * @param Source Starting location of the projectile's flight
	 * @param Target Target location for the projectile to arrive at
	 * @param LaunchSpeed The speed of the projectile at the very start of its flight, in cm/s
	 * @param GravityAcceleration Acceleration due to gravity, in cm/s^2. Downward acceleration is negative
	 * @param bCalculateAlternateTrajectory If true, calculates an alternate trajectory that arcs even higher
	 * This projectile's flight may be very long
	 * @param OutTrajectory Out parameter with desired angle to fire the projectile at, in degrees
	 * @param OutTime Out parameter with the expected time the projectile will take to reach the destination, in seconds
	 * @return True if a valid trajectory exists, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category = "Projectile Motion", meta = (ReturnDisplayName = "Valid Trajectory Found"))
	static bool GetProjectileTrajectoryAngleFromLaunchSpeed(
		FVector Source,
		FVector Target,
		float LaunchSpeed,
		float GravityAcceleration,
		bool bCalculateAlternateTrajectory,
		float& OutTrajectory,
		float& OutTime);

	/**
	 * Gets the velocity needed to shoot a freefall projectile from Source to Target given a launch speed
	 * A trajectory may not exist if LaunchSpeed is too low for the given GravityAcceleration and source-to-target distance.
	 * @param WorldContextObject World context object of the projectile
	 * @param Source Start location of the projectile's flight
	 * @param Target Target location for the projectile to arrive at
	 * @param LaunchSpeed The speed of the projectile at the very start of its flight, in cm/s
	 * @param bCalculateAlternateTrajectory If true, calculates an alternate trajectory that arcs even higher
	 * This projectile's flight may be very long
	 * @param OutVelocity The velocity needed to launch the projectile at for the desired trajectory
	 * @param OutTravelTime The predicted time the projectile will be in flight for to reach destination
	 * @return True if a valid trajectory exists, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category = "Projectile Motion", meta = (ReturnDisplayName = "Valid Trajectory Found", WorldContext = "WorldContextObject"))
	static bool GetProjectileTrajectoryVelocityFromLaunchSpeed(
		const UObject* WorldContextObject,
		FVector Source,
		FVector Target,
		float LaunchSpeed,
		bool bCalculateAlternateTrajectory,
		FVector& OutVelocity,
		float& OutTravelTime);

	/**
	 * Gets the velocity needed to shoot a freefall projectile from Source to Target
	 * given the time the projectile should be in flight for.
	 * @param WorldContextObject World context object of the projectile
	 * @param Source Start location of the projectile's flight
	 * @param Target Target location for the projectile to arrive at
	 * @param Time Desired time of flight
	 * @return Returns the launch velocity of the projectile
	 */
	UFUNCTION(BlueprintCallable, Category = "Projectile Motion", meta = (ReturnDisplayName = "Velocity", WorldContext = "WorldContextObject"))
	static FVector GetProjectileTrajectoryVelocityFromTime(
		const UObject* WorldContextObject,
		FVector Source,
		FVector Target,
		float Time);
};
