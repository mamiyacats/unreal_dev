// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "BonePresets.h"
#include "FootInfo.h"
#include "IBoneSettingsProvider.h"
#include "IHandSolver.h"
#include "BodyIKControls.h"
#include "IKControlsAlignment.h"
#include "ILocationSolver.h"
#include "IPoseSolver.h"
#include "MediaPipeAnimContext.h"
#include "MediaPipeAnimMode.h"
#include "MediaPipeAutoConnect.h"
#include "MediaPipeSource.h"
#include "MediaPipeHolisticComponent.h"
#include "MediaPipeRemapAsset.h"
#include "TransformValueType.h"
#include "Animation/AnimInstance.h"
#include "Head/IHeadSolver.h"
#include "LiveLinkInterface/Public/LiveLinkTypes.h"
#include "MediaPipeAnimInstance.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class MEDIAPIPE_API UMediaPipeAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMediaPipeAnimInstance();
	UMediaPipeSource* GetMediaPipeSource() const { return MediaPipeSource; }

	TSharedPtr<ILocationSolver> GetLocationSolver() { return LocationSolver; }
	TSharedPtr<IPoseSolver> GetPoseSolver() { return PoseSolver; }
	TSharedPtr<IHandSolver> GetHandsSolver() { return HandsSolver; }
	TSharedPtr<IHeadSolver> GetHeadSolver() { return HeadSolver; }
	TSharedPtr<FSolverUtils> GetSolverUtils() { return SolverUtils; }

	TWeakPtr<FMediaPipeAnimContext> GetContext() const;

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	void GetSolverFPS(float& AnimationFPS, float& MediaPipeFPS);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	EMediaPipeAnimMode Mode = EMediaPipeAnimMode::FullBody;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	FVector NoseLocationToHead = FVector(0, 0.01, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	bool ResetOnPipelineStopped = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	bool bSolveFingers = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	bool bSolveHeadFromFaceMesh = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	bool bSolveFace = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	bool bSolveLocation = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	float MinPoseScoreThresh = 0.5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	bool bTwistCorrectionEnabled = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	EMediaPipeAutoConnect AutoConnectToMediaPipe = EMediaPipeAutoConnect::Enabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MediaPipe|LiveLink")
	FLiveLinkSubjectName LiveLinkSubject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MediaPipe|LiveLink")
	bool bLiveLinkEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MediaPipe|Debug")
	bool bDebugDraw = false;


	FVector OriginHipLocation;
	FVector OriginActorLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	EBonePresets BonePreset = EBonePresets::UE5;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MediaPipe",  meta=(EditCondition="BonePreset == EBonePresets::Custom"))
	TObjectPtr<UMediaPipeRemapAsset> BoneRemap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MediaPipe")
	TObjectPtr<UPoseAsset> PoseAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MediaPipe")
	FName PoseForInit = NAME_None;
	
	virtual void NativeBeginPlay() override;

	TWeakPtr<FHumanoidBoneSettings> GetBoneSettings();

	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	bool IsMediaPipeRunning();

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	bool IsPaused() const;

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	void Pause() const;

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	void Resume() const;

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	bool ConnectToMediaPipeInLevel();

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	bool ConnectToMediaPipe(UMediaPipeHolisticComponent* MediaPipeComponent);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	bool IsMediaPipeConnected() const;

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	void DisconnectFromMediaPipe();
	
	virtual bool ReInitialize(TSharedPtr<IBoneSettingsProvider> = nullptr);

	UFUNCTION(BlueprintPure, Category="MediaPipe", meta=(BlueprintThreadSafe))
	bool GetBodyControlIK(EBoneControlSpace Space,ETransformValueType ValueType,FBodyIKControls& IKControls) const;

	FIKControlsAlignment* GetIKControlsAlignment() const;
protected:
	void PrepareSolvers(IBoneSettingsProvider* Provider);
	TSharedRef<FHumanoidBoneSettings> BoneSettings = MakeShared<FHumanoidBoneSettings>();

	virtual void OnBoneSettingsApplied(FHumanoidBoneSettings& Settings) {};
   
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUninitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
	virtual void HandlePoseOut(const TSharedPtr<TArray<FMediaPipeLandmark>>& Landmarks, const FMediaPipeSourceInfo& SourceInfo);
	virtual void HandlePoseWorldOut(const TSharedPtr<TArray<FMediaPipeLandmark>>& Landmarks, const FMediaPipeSourceInfo& SourceInfo);
	virtual void HandleFaceGeometryOut(const TSharedPtr<FMediaPipeFaceMesh>& FaceGeometry, const FMediaPipeSourceInfo& SourceInfo);
	virtual void HandleFaceLandmarksOut(const TSharedPtr<TArray<FMediaPipeLandmark>>& Landmarks, const FMediaPipeSourceInfo& SourceInfo);
	virtual void HandleLeftHandOut(const TSharedPtr<TArray<FMediaPipeLandmark>>& Landmarks, const FMediaPipeSourceInfo& SourceInfo);
	virtual void HandleRightHandOut(const TSharedPtr<TArray<FMediaPipeLandmark>>& Landmarks, const FMediaPipeSourceInfo& SourceInfo);
	virtual void HandleMediaPipeHolisticStopped(UMediaPipeHolisticComponent* Component);
	virtual void HandleBeforeMediaPipeHolisticStart(UMediaPipeHolisticComponent* Component, IMediaPipeImageSource* Source);
	virtual void HandleMediaPipeHolisticStarted(UMediaPipeHolisticComponent* Component);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	void ResetAllSolvers();

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	void EnableAllSolvers(bool bIsEnabled);

private:
	UPROPERTY(Transient)
	TWeakObjectPtr<UMediaPipeHolisticComponent> MediaPipeHolisticComponent;
	
	UPROPERTY(Transient)
	TObjectPtr<UMediaPipeSource> MediaPipeSource;

	bool bBoneCached = false;

	void RegisterEventHandler();
	void UnRegisterEventHandler() const;

	

	void DrawIKChain(const FVector& A, const FVector& B, const FVector& C);

	FFootInfo HintFoot(EFootType FootType) const;

	TSharedPtr<IPoseSolver> PoseSolver;
	TSharedPtr<ILocationSolver> LocationSolver;
	TSharedPtr<IHandSolver> HandsSolver;
	TSharedPtr<IHeadSolver> HeadSolver;
	TSharedPtr<FMediaPipeAnimContext> SharedContext;
	TSharedPtr<FSolverUtils> SolverUtils;

	static void UpdateSolverEnabled(TWeakObjectPtr<UMediaPipeHolisticComponent>Component, UMediaPipeAnimInstance* AnimInstance);
};


