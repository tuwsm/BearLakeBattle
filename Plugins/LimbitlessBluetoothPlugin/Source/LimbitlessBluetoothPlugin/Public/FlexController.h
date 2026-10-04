// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "Tickable.h"
#include "UObject/Object.h"
#include "SensorData.h"
#include "CalibrationData.h"
#include "Managers/BluetoothManager.h"
#include "FlexController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAnalogReceivedFlexSignature, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRotationReceivedSignature, FVector, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAccelerationReceivedSignature, FVector, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAngularVelocityReceivedSignature, FVector, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDiscreteReceivedFlexSignature, int, Level);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDiscreteThresholdReachedSignature, int, Level);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCalibrationStartedSignature, float, Duration);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCalibrationEndedSignature);

DECLARE_DELEGATE(FDeviceTimeOutSignature);

UCLASS(BlueprintType)
class LIMBITLESSBLUETOOTHPLUGIN_API UFlexController : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
public:
	const FString& GetDeviceID() const {return DeviceID;}
	const FSensorData& GetSensorData() const;

	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickableInEditor() const override{return false;}
	virtual bool IsTickableWhenPaused() const override{return true;}

	UPROPERTY(BlueprintAssignable)
	FOnRotationReceivedSignature OnRotationReceived;

	UPROPERTY(BlueprintAssignable)
	FOnAngularVelocityReceivedSignature OnAngularVelocityReceived;
	
	UPROPERTY(BlueprintAssignable)
	FOnAccelerationReceivedSignature OnAccelerationReceived;
	
	// A value from 0-1, where 0 is rest threshold and 1 is maximum flex
	UPROPERTY(BlueprintAssignable)
	FAnalogReceivedFlexSignature OnAnalogFlex;
	
	// Passes discrete level ranging from 1 to NumDiscreteLevels
	UPROPERTY(BlueprintAssignable)
	FDiscreteReceivedFlexSignature  OnDiscreteFlex;

	UPROPERTY(BlueprintAssignable)
	FDiscreteThresholdReachedSignature OnDiscreteThresholdReached;

	UPROPERTY(BlueprintAssignable)
	FOnCalibrationStartedSignature OnStartRestCalibration{};

	UPROPERTY(BlueprintAssignable)
	FOnCalibrationStartedSignature OnStartFlexCalibration{};

	UPROPERTY(BlueprintAssignable)
	FOnCalibrationEndedSignature OnFinishFlexCalibration{};

	UPROPERTY(BlueprintAssignable)
	FOnCalibrationStartedSignature OnStartIMUCalibration{};

	UPROPERTY(BlueprintAssignable)
	FOnCalibrationEndedSignature OnFinishIMUCalibration{};
	
	FDeviceTimeOutSignature OnDeviceTimedOut;
	FOnFlexDisconnectedSignature OnDeviceDisconnected;

	
	FQuat GetCurRot() const{ return Rotation; }
	FVector GetCoordinateAcceleration() const { return CoordinateAcceleration; }
	int GetRestThreshold() const{ return CalData.RestThreshold; }
	int GetDiscreteLevel(double Flex) const;
	int GetDiscreteLevel() const;
	bool bIsCalibrating() const { return !!ProcessCalibration; }

	UFUNCTION(BlueprintCallable, Category = "Calibration")
	void BeginIMUCalibration();
	
	UFUNCTION(BlueprintCallable, Category = "Calibration")
	void BeginFlexCalibration();

	static constexpr int NumDiscreteLevels{ 3 };

	/*
	 *  OVERRIDE IT FOR PLATFORM SPECIFIC BLUETOOTH!
	*	Sets the scale for the flex controller associated with the player num.
	*	CALL THIS FUNCTION VERY SPARINGLY! Currently, flex controller scales can only be written to
	*	a fixed number of times.
	* 
	*	@param scale Sets the scale of the device. This "zooms in" the data that the device captures for more granularity.
	*	@param scaleSetCallback Function to call when the new scale is successfully written
	*/
	virtual void SetScale(uint8 scale, TFunction<void()> scaleSetCallback);
	virtual void SetColor(EFlexColor color, TFunction<void()> colorSetCallback);
protected:
	// Parses raw packet data into SensorData
	void ProcessRawData(const TArray<uint8>& RawData);

	// Uses processed sensor data to counteract biases and update orientation
	void HandleProcessedData();

	void CalibrateIMU(const FSensorData& Data, float DeltaTime);
	void CalibrateRestThreshold(const FSensorData& Data, float DeltaTime);
	void CalibrateScale(const FSensorData& Data, float DeltaTime);

	UPROPERTY(EditAnywhere, Category = "Calibration")
	float CoordinateAccelerationThreshold{1.f};

protected:
	FString DeviceID;
	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	FSensorData SensorData;
	
protected:
	static std::vector<uint8> CreateCharacteristicPacket(EFlexColor ColorData, uint8 Scale);
	// Returns quaternion raised to the power. Normalizes the result
	static FQuat QuatNormPow(FQuat Quat, double exp);
	// Gets the rotation needed to transform the current orientation to the orientation of gravity as read by the accelerometer
	static FQuat GetGravityDifference(FQuat curRot, FVector accel);
	
	/** Updates the given Quaternion rotation based on sensor data
	*	
	*	@param CurRot The current rotation of the device
	*	@param Gyro The sensor reading from the gyroscope
	*	@param Accel The sensor reading from the accelerometer
	*	@param DeltaTime The time since the last orientation update
	*/ 
	void BroadcastFlexInput();
	void BroadcastDiscrete();
	void BroadcastAnalog() const;
	void BroadcastRotation() const;
	void BroadcastAngularVelocity() const;
	void BroadcastAcceleration() const;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Disconnection")
	float TimeoutDelay{ .25 };

	FQuat Rotation{ FQuat::Identity };
	FQuat LastRotation{ FQuat::Identity };

	// Global velocity in worldspace. Gyroscope readings are device local coords
	FVector CoordinateAcceleration{ FVector::ZeroVector };

	// Updates orientation of device from accelerometer and gyroscope data
	void UpdateOrientation(FQuat& CurRot, FVector Gyro, FVector Accel, float DeltaTime);
	
	// Updates coordinate acceleration from accelerometer and orientation
	void UpdateCoordinateAcceleration();
	
	// How much the accelerometer data, interpreted as world up, should be considered when calculating device orientation
	const double GravityFactor{ .05 };
	/*
	 *  Calibration things
	 */
	FCalibrationData CalData{};
	float CalibrationTimer{ 0 };
	
	int RestPadding{ 400 };
	
	float RestTime{ 2 };
	float FlexTime{ 2 };
	float IMUTime{ 2 };
	int ScaleFactor{ 1200 };

	double TimeLastPacketReceived{ DBL_MAX };
	void ParseRawData(const TArray<uint8>& RawData);
	
	TFunction<void(const FSensorData&, float DeltaTime)> ProcessCalibration{};
	
	TArray<TArray<double>> AccelCalibrationValues{ {},{},{} };
	TArray<TArray<double>> GyroCalibrationValues{ {},{},{} };
	TArray<int> FlexCalibrationValues;

	bool bIsFlexing{};
	float CurrentFlexMax{};
	int CurrentLevelMax{};
};


