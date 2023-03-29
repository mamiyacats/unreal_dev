// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "CameraParams.h"
#include "DynamicTexture.h"
#include "MediaPipeFaceMesh.h"
#include "MediaPipeHolisticOptions.h"
#include "MediaPipeImageSource.h"
#include "MediaPipeLandmark.h"
#include "MediaPipeSourceInfo.h"
#include "VideoDisplay.h"
#include "WebcamImageSourceComponent.h"
#include "Components/ActorComponent.h"
#include "MediaPipeHolisticComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnVideoTextureCreated, UTexture2D*, NewTexture, int, TextureWidth, int, TextureHeight);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMediaLifeCycle);

class FMediaPipeConnector;

UCLASS(ClassGroup="MediaPipe", meta=(BlueprintSpawnableComponent))
class MEDIAPIPE_API UMediaPipeHolisticComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	DECLARE_EVENT_TwoParams(UMediaPipeHolisticComponent, FBeforeMediaPipeHolisticStart, UMediaPipeHolisticComponent*, IMediaPipeImageSource*);
	DECLARE_EVENT_OneParam(UMediaPipeHolisticComponent, FOnMediaPipeHolisticStateChanged, UMediaPipeHolisticComponent*);
	DECLARE_EVENT_TwoParams(UMediaPipeHolisticComponent, FLandmarksOutEvent, const TSharedPtr<TArray<FMediaPipeLandmark>>&, const FMediaPipeSourceInfo&);
	DECLARE_EVENT_TwoParams(UMediaPipeHolisticComponent, FaceGeometryOutEvent, const TSharedPtr<FMediaPipeFaceMesh>&, const FMediaPipeSourceInfo&);
	//multi_face_geometry
	FLandmarksOutEvent& PoseLandmarksEventTrigger() { return PoseLandmarksEvent; }
	FLandmarksOutEvent& LeftHandLandmarksEventTrigger() { return LeftHandLandmarksEvent; };
	FLandmarksOutEvent& RightHandLandmarksEventTrigger() { return RightHandLandmarksEvent; }
	FLandmarksOutEvent& FaceLandmarksEventTrigger() { return FaceLandmarksEvent; }
	FLandmarksOutEvent& PoseWorldLandmarksEventTrigger() { return PoseWorldLandmarksEvent; }
	FaceGeometryOutEvent& FaceGeometryEventTrigger() { return FaceGeometryEvent; }
	
	// Sets default values for this component's properties
	UMediaPipeHolisticComponent();
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	IMediaPipeImageSource* GetCurrentImageSource() const;

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	bool IsNativeImageSource() const;

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	bool IsWebcamCapture();

	UFUNCTION(BlueprintCallable, Category="MediaPipe") 
	bool GetImageSourceFPS(float& SourceFrameRate, float& StreamingFrameRate);

	UFUNCTION(Category="MediaPipe", BlueprintCallable)
	FCameraParams  GetCurrentCameraParams();
	
	UFUNCTION(Category="MediaPipe", BlueprintCallable)
	bool StartCamera(int DeviceId = 0, int ResolutionX = 1280, int ResolutionY = 720, int FPS = 30);

	UFUNCTION(Category="MediaPipe", BlueprintCallable)
	bool StartImageSource(const TScriptInterface<IMediaPipeImageSource>& ImageSource);

	UFUNCTION(Category="MediaPipe", BlueprintCallable)
	float GetSourceTextureAspectRatio() const { return MediaPipeSourceInfo.IsValid() ? static_cast<float>(MediaPipeSourceInfo.ImageWidth) / MediaPipeSourceInfo.ImageHeight : 0.0f; }

	UFUNCTION(Category="MediaPipe", BlueprintCallable)
	virtual void Stop();

	UFUNCTION(Category="MediaPipe", BlueprintCallable)
	bool IsRunning();

	UPROPERTY(Category="MediaPipe", BlueprintReadWrite, EditAnywhere)
	EVideoDisplay VideoDisplay = EVideoDisplay::Raw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	FMediaPipeHolisticOptions Options;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="MediaPipe", Transient)
	FMediaPipeSourceInfo MediaPipeSourceInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	int GraphTimeoutSeconds = 10;

	FOnMediaPipeHolisticStateChanged& OnMediaPipeHolisticStoppedTrigger() { return OnStoppedEvent; }
	FBeforeMediaPipeHolisticStart& BeforeMediaPipeHolisticStartTrigger() { return BeforeStartEvent;  }
	FOnMediaPipeHolisticStateChanged& OnMediaPipeHolisticStartedTrigger() { return OnStartedEvent; }

	UFUNCTION(Category="MediaPipe", BlueprintCallable)
	bool IsStaticImageSource();

	bool StartImageSource(IMediaPipeImageSource* ImageSource);

	//Blueprint Events
	UPROPERTY(Category="MediaPipe|Events", BlueprintAssignable)
	FOnVideoTextureCreated OnVideoTextureCreated;
	
	UPROPERTY(Category="MediaPipe|Events", BlueprintAssignable)
	FOnMediaLifeCycle OnMediaPipeInitialized;

	UPROPERTY(Category="MediaPipe|Events", BlueprintAssignable)
	FOnMediaLifeCycle OnMediaPipeStarted;

	UPROPERTY(Category="MediaPipe|Events", BlueprintAssignable)
	FOnMediaLifeCycle OnMediaPipeStopped;

	UPROPERTY(Category="MediaPipe | Events", BlueprintAssignable)
	FOnMediaLifeCycle OnMediaPipeThreadFault;

	//ImageSource
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe|ImageSource")
	EResolutionLimits  SourceResolutionLimits = EResolutionLimits::P720_16_9;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe|ImageSource")
	bool  bSourceHorizontalFlip = false;
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
 	virtual bool HandlePoseLandmarks(class IUmpObserver* Observer, void* Packet);
	virtual bool HandleLeftHandLandmarks(class IUmpObserver* Observer, void* Packet);
	virtual bool HandleRightHandLandmarks(class IUmpObserver* Observer, void* Packet);
	virtual bool HandleFaceLandmarks(class IUmpObserver* Observer, void* Packet);
	virtual bool HandlePoseWorldLandmarks(class IUmpObserver* Observer, void* Packet);
	virtual bool HandleFaceGeometry(class IUmpObserver* Observer, void* Packet);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MediaPipe")
	TObjectPtr<UWebcamImageSourceComponent> WebcamSource;
private:
	typedef bool (UMediaPipeHolisticComponent::*PacketCallback)(class IUmpObserver* Observer, void* Packet);

	FLandmarksOutEvent PoseWorldLandmarksEvent;
	FLandmarksOutEvent PoseLandmarksEvent;
	FLandmarksOutEvent LeftHandLandmarksEvent;
	FLandmarksOutEvent RightHandLandmarksEvent;
	FLandmarksOutEvent FaceLandmarksEvent;
	FaceGeometryOutEvent FaceGeometryEvent;

	TMap<FString, IUmpObserver*> Observers;
	
	bool bIsPipelineRunning;

	TUniquePtr<FDynamicTexture> VideoTexture;

	UPROPERTY()
	TScriptInterface<IMediaPipeImageSource> ScriptImageSource;
	IMediaPipeImageSource* NativeImageSource;

	FCameraParams CurrentCamera;

	//pipeline linstener
	virtual void OnFrameOut(TSharedPtr<IMediaPipeOutFrame>& InMat);
	bool StartInternal(IMediaPipeImageSource* InImageSource);
	void StopInternal(long long SessionId);

	virtual  void OnPipelineWorkThreadFault(long long SessionId);
	virtual void OnExitPipelineWorkThread(long long SessionId);
	virtual void OnEnterPipelineWorkThread(long long SessionId);
	virtual  void OnImageSizeReceived(int Width, int Height);
	void SetCurrentImageSource(IMediaPipeImageSource* ImageSource);
	
	void SetupObservers();
	void ClearObservers();

	void CreateObserver(FString StreamName, PacketCallback Callback);
	
	UFUNCTION()
	void RaiseTextureCreated(UTexture2D* Texture, int Width, int Height);

	FBeforeMediaPipeHolisticStart BeforeStartEvent;
	FOnMediaPipeHolisticStateChanged OnStoppedEvent;
	FOnMediaPipeHolisticStateChanged OnStartedEvent;
	
	friend FMediaPipeConnector;
private:
	mutable FCriticalSection StateCS;
	int64 CurrentSessionId = 0;
	bool bInitialized = false;
};
