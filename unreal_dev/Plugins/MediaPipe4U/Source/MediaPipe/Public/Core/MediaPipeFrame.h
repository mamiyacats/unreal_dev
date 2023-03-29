// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "CoreMinimal.h"
#include "MediaPipeFaceMesh.h"
#include "MediaPipeLandmark.h"
#include "MediaPipeSourceInfo.h"

class UMediaPipeSource;

struct MEDIAPIPE_API FMediaPipeFrame
{
	int64 FrameId = -1;
	FMediaPipeSourceInfo SourceInfo;
	bool bIsNew;
	
	bool IsValid() const;
	TArray<FMediaPipeLandmark>& GetLandmarks() const;
private:
	TSharedPtr<TArray<FMediaPipeLandmark>> Landmarks;
	friend class UMediaPipeSource;
};

struct MEDIAPIPE_API FMediaPipeFaceGeometryFrame
{
	int64 FrameId = -1;
	
	bool IsValid() const;
	FMediaPipeFaceMesh& GetFaceMesh() const;
private:
	TSharedPtr<FMediaPipeFaceMesh> Mesh;
	friend class UMediaPipeSource;
};
