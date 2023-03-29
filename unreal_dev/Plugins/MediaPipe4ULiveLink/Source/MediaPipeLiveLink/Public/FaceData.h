// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "MediaPipeFaceMesh.h"
#include "MediaPipeLandmark.h"

class UMediaPipeLiveLinkComponent;

struct MEDIAPIPELIVELINK_API FFaceData
{
	FFaceData() {}
	const TArray<FMediaPipeLandmark>& GetLandmarks() const;
	const TArray<FMediaPipeLandmark>& GetGeometryLandmarks() const;
private:
	TSharedPtr<TArray<FMediaPipeLandmark>> Landmarks;
	TSharedPtr<FMediaPipeFaceMesh> Geometry;
	friend class UMediaPipeLiveLinkComponent;
};