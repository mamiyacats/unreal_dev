// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "GstAppSinkComponent.h"
#include "GstPipelineComponent.h"
#include "MediaPipeImageSourceComponent.h"
#include "GStreamerImageSourceComponent.generated.h"


UCLASS(ClassGroup="MediaPipe", meta=(BlueprintSpawnableComponent))
class MEDIAPIPEGSTREAMER_API UGStreamerImageSourceComponent : public UMediaPipeImageSourceComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	UGStreamerImageSourceComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GStreamer")
	FString FilePath;

	UFUNCTION(BlueprintGetter, Category="GStreamer")
	UGstPipelineComponent* GetPipeline() const { return GStreamerPipeline; }

	UFUNCTION(BlueprintGetter, Category="GStreamer")
	UGstAppSinkComponent* GetSink() const { return GStreamerSink; }
	
	UFUNCTION(BlueprintCallable, Category="GStreamer")
	bool Start(const FString& File);
	UFUNCTION(BlueprintCallable, Category="GStreamer")
	void Stop();
	void SafeRemoveEventHandlers();

	UFUNCTION(BlueprintGetter, Category="GStreamer")
	bool IsRunning() const { return bIsRunning; }

	UFUNCTION(BlueprintCallable, Category="GStreamer")
	bool Pause();

	UFUNCTION(BlueprintCallable, Category="GStreamer")
	void Resume();

	UFUNCTION(BlueprintCallable, Category="GStreamer")
	bool Seek(float Percent);

	//MediaPipeImageSource Impl
	virtual bool IsSupportLimitResolution() override;
	virtual bool IsSupportHorizontalFlip() override;

protected:
	// Called when the game starts
	virtual void UninitializeComponent() override;
	virtual  void InitializeComponent() override;
	FString BuildTransformElement() const;
	
	UPROPERTY(BlueprintGetter=GetPipeline, Category="GStreamer")
	UGstPipelineComponent* GStreamerPipeline;

	UPROPERTY(BlueprintGetter=GetSink, Category="GStreamer")
	UGstAppSinkComponent* GStreamerSink;

	UPROPERTY(VisibleAnywhere, BlueprintGetter=IsRunning, Category="GStreamer")
	bool bIsRunning = false;
	bool bIsTextureChanged = false;


	FDelegateHandle TextureUpdateHandler;

	UFUNCTION()
	void OnHandleTextureCreated(UGstAppSinkComponent* AppSink, UTexture2D* NewTexture, EGstVideoFormat Format, int Width, int Height);

	UFUNCTION()
	void OnHandleTextureUpdated(FGstTextureContext& Context);

	UFUNCTION(BlueprintImplementableEvent, Category="GStreamer")
	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void OnStateChanged(EGstPipelineState OldState, EGstPipelineState NewState);
};
