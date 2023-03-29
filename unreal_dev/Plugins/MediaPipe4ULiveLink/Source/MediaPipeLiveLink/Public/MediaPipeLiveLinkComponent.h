// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "BlendShapeSettings.h"
#include "FaceData.h"
#include "IMediaPipeLiveLinkSource.h"
#include "MediaPipeHolisticComponent.h"
#include "Components/ActorComponent.h"
#include "MediaPipeLiveLinkComponent.generated.h"




UCLASS(ClassGroup="MediaPipe", meta=(BlueprintSpawnableComponent))
class MEDIAPIPELIVELINK_API UMediaPipeLiveLinkComponent : public UActorComponent
{
	DECLARE_EVENT_OneParam(UMediaPipeLiveLinkComponent, FCalibrationCompletedEvent, const FFaceMeasurements&)
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MediaPipe")
	FName LiveLinkSubjectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MediaPipe")
	bool bAutoStartMediaPipeWhenBeginCalibration = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	float EyesSmooth = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	float FaceSmooth = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	float AlgorithmicDeNoise = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bDisabled = false;
	
	// Sets default values for this component's properties
	UMediaPipeLiveLinkComponent();

	UFUNCTION(BlueprintCallable, Category = "MediaPipe")
	FRotator GetHeadRotator();

	UFUNCTION(BlueprintCallable, Category = "MediaPipe")
	void BeginCalibration(int CameraDeviceId = 0);

	UFUNCTION(BlueprintCallable, Category = "MediaPipe")
	bool EndCalibration(FFaceMeasurements& OutSettings);

	UFUNCTION(BlueprintCallable, Category = "MediaPipe")
	bool LoadSettings(const FFaceMeasurements& InSetting);

	FCalibrationCompletedEvent& CalibrationCompletedEventTrigger();
protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	bool bIsInCalibrating;
	bool bNeedCloseMediaPipeOnEnd = false;
	TSharedPtr<IMediaPipeLiveLinkSource> Source;
	UPROPERTY()
	TObjectPtr<UMediaPipeHolisticComponent> MediaPipeHolisticComponent;

	TSharedPtr<TArray<FMediaPipeLandmark>> Landmarks;
	TSharedPtr<FMediaPipeFaceMesh> FaceMesh;
	TArray<FFaceData> TempFaceData;
	void OnMediaPipeStarted(UMediaPipeHolisticComponent* Owner);
	void SubscribeMediaPipeEvents();
	void UnsubscribeMediaPipeEvents(); 
	void OnMediaPipeStopped(UMediaPipeHolisticComponent* Owner);

	void HandleFaceMesh(const TSharedPtr<TArray<FMediaPipeLandmark>>& FaceMeshes, const FMediaPipeSourceInfo& SourceInfo);
	void HandleFaceGeometry(const TSharedPtr<FMediaPipeFaceMesh>& FaceMeshes, const FMediaPipeSourceInfo& SourceInfo);
	
	void AddLiveLinkSource();
	void RemoveLiveLinkSource();
	void SolveFace();

	FCalibrationCompletedEvent CalibrationCompletedEvent;
	FRotator HeadRotator;
	FCriticalSection SourceLock;
	FCriticalSection SubLock;
	FCriticalSection DataLock;
	std::atomic<bool> bDataLock;
	FMediaPipeSourceInfo MediaPipeSourceInfo;
	bool bEventSubscribed = false;
};


