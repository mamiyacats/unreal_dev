// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "CoreMinimal.h"
#include "ARTrackable.h"
#include "BlendShapeSettings.generated.h"

USTRUCT(BlueprintType)
struct MEDIAPIPELIVELINK_API FBlendShapeConfig
{
	GENERATED_BODY()
	
	FBlendShapeConfig(float GeometryMinValue, float GeometryMaxValue): Min(GeometryMinValue),
	                                                                         Max(GeometryMaxValue)
	{
	}

	FBlendShapeConfig(): Min(0),Max(0)
	{
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MediaPipe")
	float Min = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MediaPipe")
	float Max = 0.0f;
};

UENUM(BlueprintType)
enum class ECalibrationKey : uint8
{
	EyeOpenLeft,
	EyeOpenRight,
	MouthWidth,
	MouthOpen,
	SmileRatio,
	EyeInner,
	EyeOuter,
	MouthLeftRight,
};

USTRUCT(BlueprintType)
struct MEDIAPIPELIVELINK_API FFaceMeasurements
{
	GENERATED_BODY()

	FFaceMeasurements();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	TMap<ECalibrationKey, FBlendShapeConfig> Values;
};

