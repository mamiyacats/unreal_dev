// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "FaceData.h"
#include "ILiveLinkSource.h"
#include "MediaPipeSourceInfo.h"

class MEDIAPIPELIVELINK_API IMediaPipeLiveLinkSource : public ILiveLinkSource
{
public:
	virtual void Active() = 0;
	virtual void Deactivate() = 0;
	virtual void PublishFaceMesh(const FFaceData& FaceData, const FMediaPipeSourceInfo& SourceInfo) = 0;
};
