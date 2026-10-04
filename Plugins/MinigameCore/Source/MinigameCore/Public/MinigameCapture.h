// Copyright Limbitless Solutions, Inc. All Rights Reserved


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MinigameCapture.generated.h"

class USceneCaptureComponent2D;
class UWidgetComponent;

UCLASS()
class MINIGAMECORE_API AMinigameCapture : public AActor
{
	GENERATED_BODY()
	
public:	
	AMinigameCapture();

	UFUNCTION(BlueprintCallable, Category = "Effects")
	void ApplyCameraShake(float Intensity, float Duration);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Capture Info")
	TObjectPtr<USceneCaptureComponent2D> SceneCapture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture Info")
	int CaptureNumber{ 0 };

	virtual void Tick(float DeltaTime) override;

private:
	float CameraShakeIntensity{};

public:
	UFUNCTION(BlueprintCallable, Category = "Capture Info")
	int GetCaptureNumber() const { return CaptureNumber; }

	void EnableCamera(bool bIsEnabled);

	UFUNCTION(BlueprintCallable, Category = "Projection")
	bool ProjectWorldToCapture(const FVector& WorldPosition, FVector2D& OutScreenPosition) const;

	UFUNCTION(BlueprintCallable, Category = "Effects")
	float GetShakeIntensity() const { return CameraShakeIntensity; }

	UFUNCTION(BlueprintCallable, Category = "Effects")
	void SetShakeIntensity(float Intensity) { CameraShakeIntensity = Intensity; }
};
