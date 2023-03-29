﻿// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include <functional>
#include "HumanoidBoneSettings.h"
#include "LiveLinkTypes.h"
#include "MediaPipeAnimExtensions.h"
#include "MediaPipeAnimMode.h"
#include "MediaPipeSource.h"
#include "PoseAssetContainer.h"
#include "TwistCorrectionSettings.h"

struct MEDIAPIPE_API FMediaPipeBoneTransform
{
	FName BoneName;
	FTransform Transform;
	FTransform LocalTransform;
};

class UMediaPipeAnimInstance;
class FSolverUtils;

class MEDIAPIPE_API FMediaPipeAnimContext
{
public:
	typedef std::function<void(IMediaPipeAnimExtensions* Extension)> ExtensionAction;
	FMediaPipeAnimContext(TWeakPtr<FHumanoidBoneSettings> BoneConfig): BoneSettings(BoneConfig)
	{
		
	}
	TArray<TWeakObjectPtr<UObject>> Extensions;
	TWeakPtr<FHumanoidBoneSettings> BoneSettings;
	TWeakObjectPtr<UMediaPipeSource> MediaPipeSource;

	TOptional<FRotator> BodyRotator;

	EMediaPipeAnimMode Mode = EMediaPipeAnimMode::FullBody;
	
	bool bIsTwistCorrectionEnabled = false;
	bool bIsStaticImageSource = false;

	bool bHeadSolverRegister = false;
	bool bHandSolverRegister = false;
	bool bPoseSolverRegister = false;
	bool bLocationSolverRegister = false;
	//bool bFaceSolverRegister = false;

	bool bLeftHandVisible = true;
	bool bRightHandVisible = true;

	int PoseHandled = 0;
	int PoseHandlerCount = 0;

	bool bIsAnimationPaused = false;

	const FTransform& GetComponentTransform();
	void ForeachExtensions(ExtensionAction Action, bool bIncludeDisabled = false);
	void ForeachExtensionsReverse(ExtensionAction Action, bool bIncludeDisabled = false);
	FTwistCorrectionSettings& GetTwistCorrectionSettings();
	bool IsDebugDrawEnabled() const;
	bool NeedIgnorePose();
	bool IsSolveHead() const;
	bool IsSolveFingers() const;
	bool IsLiveLinkEnabled() const;
	bool IsMediaPipeRunning() const;
	FLiveLinkSubjectName GetLiveLinkSubject() const;
	UWorld* GetWorld() const;
	bool GetLatestCSTransform(FCompactPoseBoneIndex BoneIndex, FTransform& OutLatestTransform);
	bool GetLatestLocalTransform(FCompactPoseBoneIndex BoneIndex, FTransform& OutLatestTransform);
	bool GetLatestTransform(FCompactPoseBoneIndex BoneIndex, FMediaPipeBoneTransform& OutLatestTransform);
	void SaveLatestTransform(FCSPose<FCompactPose>& Pose, const FCompactPoseBoneIndex& BoneIndex);
	void ClearLatestTransforms();
	void ForeachLatestTransforms(std::function<void(const FMediaPipeBoneTransform&)> Action);

	bool IsUpperBodyMode() const;
	bool IsFullBodyMode() const;
	bool HasSource() const;

	
	FPoseAssetContainer* GetPoseAsset() const;
	bool HasInitPoseAsset() const;
	FName GetInitPoseName() const;
	
private:
	TMap<FCompactPoseBoneIndex, FMediaPipeBoneTransform> LatestBoneTransforms;
	FTwistCorrectionSettings TwistCorrectionSettings{};
protected:
	FTransform ComponentTransform;
	bool bEnableLivelink = true;
	bool bIsMediaPipeRunning = false;
	bool bSolveHead = false;  
	bool bSolveFingers = false;
	bool bDebugDraw = false;
	UWorld* World = nullptr;
	FLiveLinkSubjectName LiveLinkSubject;
	TSharedPtr<FPoseAssetContainer> PoseAsset;
	FName InitPoseName;
	
	friend class UMediaPipeAnimInstance;
	friend class FSolverUtils;
};