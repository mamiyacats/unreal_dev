// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include <functional>

#include "CoreMinimal.h"
#include "BoneItem.h"
#include "MediaPipeAnimInstance.h"
#include "MediaPipeAnimMode.h"
#include "MediaPipeIKEffectors.h"
#include "MediaPipePluginInfo.h"
#include "TwistCorrectionResult.h"
#include "Components/Image.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Animation/AnimTypes.h"
#include "MediaPipeLandmark.h"
#include "Animation/AnimExecutionContext.h"
#include "MediaPipeUtils.generated.h"

UENUM(BlueprintType)
enum class EAnchorPosition : uint8
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	TopCenter,
	BottomCenter,
	MiddleCenter
};

UENUM(BlueprintType)
enum class EModificationMode : uint8
{
	Replace,
	Additive
};

USTRUCT(BlueprintType)
struct FSizeInt
{
	GENERATED_BODY()
	
	int Width;
	int Height;
};

UCLASS(meta=(BlueprintThreadSafe, ScriptName = "MediaPipeUtils"))
class UMediaPipeUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	template <typename InElementType>
	static void FillArray(TArray<InElementType>& Array, const int Size, std::function<InElementType ()>& ValueFactory)
	{
		Array.SetNumUninitialized(Size, true);
		for (int i = 0; i < Size; i++)
		{
			auto v = ValueFactory();
			Array[i] = v;
		}
	}
	
	static MEDIAPIPE_API FString PrintAsciiTable(const TArray<TArray<FString>>& Rows);
	static MEDIAPIPE_API FString PrintAsciiTable(const TArray<FString>& Headers, const TArray<TArray<FString>>& Rows);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API void SetLogDebug(bool Enabled);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool AnchorWidgetInCanvas(UWidget* Widget, int TextureWidth, int TextureHeight,
												float MaxImageWidthPercent, float MaxImageHeightPercent,
												EAnchorPosition AnchorPosition);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool SetTextureToImage(UImage* Image, UTexture2D* Texture, int TextureWidth, int TextureHeight,
	                                            float MaxImageWidthPercent, float MaxImageHeightPercent,
	                                            EAnchorPosition AnchorPosition);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool FindSkeletalMeshComponent(AActor* Actor,
															 USkeletalMeshComponent*& OutSkeletalMeshComponent);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool FindMediaPipeAnimationInstance(AActor* Actor,
	                                                         UMediaPipeAnimInstance*& MediaPipeAnimInstance);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool GetPoseOptimize(UMediaPipeAnimInstance* MediaPipeAnimInstance);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API void SetPoseOptimize(UMediaPipeAnimInstance* MediaPipeAnimInstance, bool bOptimize);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool GetHandOptimize(UMediaPipeAnimInstance* MediaPipeAnimInstance);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API void SetHandOptimize(UMediaPipeAnimInstance* MediaPipeAnimInstance, bool bOptimize);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool SetPoseSmooth(UMediaPipeAnimInstance* MediaPipeAnimInstance, float Smooth);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool GetPoseSmooth(UMediaPipeAnimInstance* MediaPipeAnimInstance, float& Smooth);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool SetFingerSmooth(UMediaPipeAnimInstance* MediaPipeAnimInstance, float Smooth);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool GetFingerSmooth(UMediaPipeAnimInstance* MediaPipeAnimInstance, float& Smooth);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool SetJointLocks(UMediaPipeAnimInstance* MediaPipeAnimInstance,
	                                        const FPoseSolverLockSettings& InLocks);
	
	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API FTwistCorrectionSettings GetTwistCorrectionSettings(UMediaPipeAnimInstance* MediaPipeAnimInstance); 
	
	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool SetTwistCorrectionSettings(UMediaPipeAnimInstance* MediaPipeAnimInstance,
											const FTwistCorrectionSettings& Settings); 

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool FindMediaPipeAnimationMesh(AActor* Actor, USkeletalMeshComponent*& SkeletalMeshComponent);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool SetMediaPipeAnimationMode(AActor* Character, EMediaPipeAnimMode Mode);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool ChangeModelComplexity(UMediaPipeHolisticComponent* MediaPipeComponent,
	                                                EModelComplexity ModelComplexity);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool FindSkeletalMeshComponentByName(AActor* Actor, FName ComponentName,
	                                                          USkeletalMeshComponent*& OutSkeletalMeshComponent);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API FString Base64Utf8Encode(const FString& Text);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API FString Base64Utf8Decode(const FString& EncodedText);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool ListWebcams(TArray<FString>& OutNames, UPARAM(ref)  const FName& ProviderName = FName(TEXT("OpenCV")));

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API UMediaPipeHolisticComponent* FindMediaPipeHolisticComponent(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool RefreshLicense();
	// UFUNCTION(BlueprintCallable, Category="MediaPipe")
	// static MEDIAPIPE_API UIKRigDefinition* CreateRigControl(const USkeletalMeshComponent* SkeletalMeshComponent, const FHumanoidBoneSettings& InSettings);
	//
	// UFUNCTION(BlueprintCallable, Category="MediaPipe")
	// static MEDIAPIPE_API UIKRetargeter* CreateIKRetargeter(const FRuntimeRetargetSource& From, const FRuntimeRetargetSource& To);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool IsInEditor();

	static FQuat RemoveTwist(const FTransform& InParentTransform, FTransform& InOutTransform,
	                         const FTransform& OriginalLocalTransform, const FVector& InAlignVector);
	
	static FTwistCorrectionResult CorrectTwist(
		FTransform& InOutParentLocalTransform,
		FTransform& InOutLocalTransform,
		const FTransform& OriginalLocalTransform,
		const FVector& InAlignVector,
		const FVector& InParentAlignVector,
		float Alpha,
		float InnerAngleDegree,
		float OuterAngleDegree);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool GetResolutionLimitSize(EResolutionLimits Limitation, int& LimitedWidth, int& LimitedHeight);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API FVector2D CalcImageSize(int TextureWidth, int TextureHeight, float MaxImageWidthPercent,
	                                             float MaxImageHeightPercent, int ScreenWidth, int ScreenHeight);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool LimitSizeByResolution(int TextureWidth, int TextureHeight, EResolutionLimits Limitation, FSizeInt& LimitedSize);
	
	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API bool LimitSize(int TextureWidth, int TextureHeight, int MaxWidth, int MaxHeight, FSizeInt& LimitedSize);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API FString GetDurationString(int64 Millisecond);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static MEDIAPIPE_API FMediaPipePluginInfo PluginInfo();

	static MEDIAPIPE_API TSharedPtr<IBoneSettingsProvider> CreatePresetBoneSettingsProvider(
		EBonePresets Preset, UMediaPipeRemapAsset* RemapAsset);

	// Get worldspace location of a bone
	static MEDIAPIPE_API FVector GetBoneWorldLocation(USkeletalMeshComponent* SkelComp,
	                                                  FCSPose<FCompactPose>& MeshBases,
	                                                  FCompactPoseBoneIndex BoneIndex);

	// Get worldspace transform of a bone
	static MEDIAPIPE_API FTransform GetBoneWorldTransform(USkeletalMeshComponent* SkelComp,
	                                                      FCSPose<FCompactPose>& MeshBases,
	                                                      FCompactPoseBoneIndex BoneIndex);

	// Get bonespace location of a bone
	static MEDIAPIPE_API FVector GetBoneSpaceLocation(USkeletalMeshComponent* SkelComp,
	                                                  FCSPose<FCompactPose>& MeshBases,
	                                                  FCompactPoseBoneIndex BoneIndex);

	// Get bonespace transform of a bone
	static MEDIAPIPE_API FTransform GetBoneSpaceTransform(USkeletalMeshComponent* SkelComp,
	                                                      FCSPose<FCompactPose>& MeshBases,
	                                                      FCompactPoseBoneIndex BoneIndex);

	// Get component space location of a bone
	static MEDIAPIPE_API FVector GetBoneCSLocation(FCSPose<FCompactPose>& MeshBases, FCompactPoseBoneIndex BoneIndex);

	// Get component space transform of a bone
	static MEDIAPIPE_API FTransform GetBoneCSTransform(FCSPose<FCompactPose>& MeshBases,
	                                                   FCompactPoseBoneIndex BoneIndex);

	static MEDIAPIPE_API TOptional<FBoneTransform> GetBoneTransform(const FTransform& ComponentTransform, FCSPose<FCompactPose>& Pose,
																	FCompactPoseBoneIndex BoneIndex,
																	EBoneControlSpace BoneSpace);

	static MEDIAPIPE_API TOptional<FBoneTransform> GetBoneTransform(FComponentSpacePoseContext& Context,
	                                                                FCompactPoseBoneIndex BoneIndex,
	                                                                EBoneControlSpace BoneSpace);

	static MEDIAPIPE_API TOptional<FBoneTransform> RotateBone(
		FComponentSpacePoseContext& Context,
		const FCompactPoseBoneIndex& BoneIndex,
		const FQuat& InRotation,
		EBoneControlSpace BoneSpace = BCS_ComponentSpace,
		EModificationMode Mode = EModificationMode::Replace,
		float Smooth = 0);

	
	static MEDIAPIPE_API std::string ConvertToUTF8(const FString& Str);
	// static MEDIAPIPE_API bool BuildBoneIndices(const FAnimInstanceProxy* AnimInstanceProxy, const FName& BoneName, FSkeletonBone& OutBone);
	// static MEDIAPIPE_API void BuildBoneIndices(const FBoneContainer& RequiredBoneContainer, const FBoneReference& BoneReference, FSkeletonBone& OutBone);
	static MEDIAPIPE_API void BuildBoneIndices(const FBoneContainer& RequiredBoneContainer, FMeshPoseBoneIndex MeshBoneIndex, FSkeletonBone& OutBone);
	static MEDIAPIPE_API void BuildBoneIndices(const FBoneContainer& RequiredBoneContainer, FCompactPoseBoneIndex PoseBoneIndex, FSkeletonBone& OutBone);
	
	static MEDIAPIPE_API bool GetAllBonesInComponentSpace(const UAnimInstance* AnimInstance,
	                                                      TMap<FName, FBoneItem>& OutBones);

	static MEDIAPIPE_API bool GetHeadTowardsFromFaceMesh(const TArray<FMediaPipeLandmark>& FaceMeshes, FVector& Forward, FVector& Up, std::function<FVector(int Index, const FVector&)> Filter);

	static MEDIAPIPE_API bool GetHeadTowardsFromFaceMesh(const TArray<FMediaPipeLandmark>& FaceMeshes, FVector& Forward, FVector& Up);

	static MEDIAPIPE_API FRotator CalculateBodyRotatorFromLandmarks(const TArray<FMediaPipeLandmark>& PoseLandmarks);
	static MEDIAPIPE_API FRotator CalculateHeadRotatorFromFaceMesh(const TArray<FMediaPipeLandmark>& FaceMeshes);

	static MEDIAPIPE_API void BuildBoneChainChildToParent(const FCSPose<FCompactPose>& Pose, const FBoneReference& RootBone, const FBoneReference& TipBone, TArray<FCompactPoseBoneIndex>& OutBoneChain);
	static MEDIAPIPE_API void BuildBoneChainParentToChild(const FCSPose<FCompactPose>& Pose, const FBoneReference& RootBone, const FBoneReference& TipBone, TArray<FCompactPoseBoneIndex>& OutBoneChain);

	static MEDIAPIPE_API bool GetBoneName(const FCompactPose& Pose, FCompactPoseBoneIndex CompactPoseBoneIndex, FName& BoneName);
	static MEDIAPIPE_API bool GetBoneName(const FCompactPose& Pose, FMeshPoseBoneIndex MeshPoseBoneIndex, FName& BoneName);
	
	static const MEDIAPIPE_API TArray<FMediaPipeLandmark> EmptyLandmarks;

	static MEDIAPIPE_API FString GetThirdPartyBinariesFolder(const FString& PluginName, const FString& ThirdPartyFolderName);

	/**
	 * @brief 
	 * @param Date always use __DATE__ marco
	 * @return 
	 */
	static MEDIAPIPE_API FString GetCompiledTime(const char* Date);
};



