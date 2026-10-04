#pragma once
#include "SensorData.generated.h"

UENUM(BlueprintType, Category = "Sensor Data")
enum class EFlexColor : uint8
{
	// Flex controller takes in color data like binary in base 10
	// Each color is created by either presence or absence of each RGB component
	EFC_None	=   0,
	EFC_Blue	=   1,
	EFC_Green	=  10,
	EFC_Cyan	=  11,
	EFC_Red		= 100,
	EFC_Magenta = 101,
	EFC_Yellow	= 110,
	EFC_White	= 111,
};

USTRUCT(BlueprintType)
struct FSensorData 
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	int EMGReading;
	
	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	FVector AngularVelocity{ FVector::ZeroVector };
	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	FVector ProperAcceleration{ FVector::ZeroVector };

	uint16 Version{};
	
	uint8 BrdVersion{};
	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	uint8 Scale{1};
	uint8 Charge{};
	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	uint8 Battery{};
	UPROPERTY(BlueprintReadOnly, Category = "Sensor Data")
	EFlexColor Color{ EFlexColor::EFC_White };
	float DeltaTime{};
};
