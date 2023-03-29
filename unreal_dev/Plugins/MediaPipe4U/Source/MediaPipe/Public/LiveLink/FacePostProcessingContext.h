// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"
#include "ImageSourceInfo.h"
#include "ARTrackable.h"

struct MEDIAPIPE_API FFacePostProcessingContext
{
	TSharedPtr<FARBlendShapeMap> BlendShapeWeights;
	bool bSucceed = false;
	FImageSourceInfo ImageSourceInfo;
};
