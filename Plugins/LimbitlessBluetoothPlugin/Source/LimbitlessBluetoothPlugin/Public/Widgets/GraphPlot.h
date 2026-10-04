// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GraphPlot.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class LIMBITLESSBLUETOOTHPLUGIN_API UGraphPlot : public UUserWidget
{
	GENERATED_BODY()

public:
	// Number of grid lines that stretch from top to bottom
	UPROPERTY(EditAnywhere, Category = "Graph Properties")
	int NumVerticalLines{ 25 };

	// Number of grid lines that stretch from left to right
	UPROPERTY(EditAnywhere, Category = "Graph Properties")
	int NumHorizontalLines{ 10 };

	UPROPERTY(EditAnywhere, Category = "Graph Properties")
	float GridLineThickness {1.f};

	UPROPERTY(EditAnywhere, Category = "Graph Properties")
	FLinearColor GridLineColor{FLinearColor::Black};

	UPROPERTY(EditAnywhere, Category = "Graph Properties")
	float MarkLineThickness {1.f};

	UPROPERTY(EditAnywhere, Category = "Graph Properties")
	FLinearColor MarkLineColor{FLinearColor::Black};
	
	UPROPERTY(EditAnywhere, Category = "Graph Properties")
	float SampleLineThickness {2.f};

	UPROPERTY(EditAnywhere, Category = "Graph Properties")
	FLinearColor SampleLineColor {FLinearColor::Blue};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Graph Properties")
	bool bAutoscaleToData{true};
	
	// The amount added to the most extreme absolute value in a data sample when setting graph vertical scaling.
	// For scaling graphs only.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph Properties")
	float MinGraphSize{25};

	// The minimum value shown on the graph. For nonscaling graphs only.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph Properties")
	float UnscaledGraphMinimum{};
	
	// The maximum value shown on the graph. For nonscaling graphs only.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph Properties")
	float UnscaledGraphMaximum{};

	// Number of values to be stored when using a simple moving average
	// If zero, there will be no SMA smoothing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph Properties")
	int MovingAverageWindowSize{};
	
	
	UFUNCTION(BlueprintCallable, Category = "Graph Data")
	void SetData(const TArray<float>& InData);

	UFUNCTION(BlueprintCallable, Category = "Graph Data")
	float GetCurrentMaxValue() const { return GraphMaximum; }

	UFUNCTION(BlueprintCallable, Category = "Graph Data")
	float GetCurrentMinValue() const { return GraphMinimum; }

	UFUNCTION(BlueprintCallable, Category = "Graph Data")
	void MarkValue(FString Key, float Value);
	
protected:
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;

private:
	void SetGraph(const TArray<float>& InData);
	void SetGraphScaled(const TArray<float>& InData);
	void SetGraphUnscaled(const TArray<float>& InData);
	
	void DrawGrid(FSlateWindowElementList& OutDrawElements, int32 LayerId, const FGeometry& AllottedGeometry) const;

	void DrawLine(FVector2f PositionA, FVector2f PositionB, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FGeometry& AllottedGeometry, FLinearColor LineColor, float LineThickness) const;

	void DrawLines(const TArray<FVector2f>& Points, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FGeometry& AllottedGeometry) const;

	void DrawMarkedValues(FSlateWindowElementList& OutDrawElements, int32 LayerId, const FGeometry& AllottedGeometry) const;
	
	float GraphMaximum{};
	float GraphMinimum{};
	
	TArray<FVector2f> GraphPoints;
	
	TMap<FString, float> MarkedValues{};
};
