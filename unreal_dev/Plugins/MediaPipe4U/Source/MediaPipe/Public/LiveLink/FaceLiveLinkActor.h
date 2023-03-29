// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FaceSmoothParams.h"
#include "IFaceDataPostProcessor.h"
#include "IFaceLinkLinkSource.h"
#include "MediaPipeHolisticComponent.h"
#include "MediaPipeImageSource.h"
#include "GameFramework/Actor.h"
#include "FaceLiveLinkActor.generated.h"

UCLASS(Abstract)
class MEDIAPIPE_API AFaceLiveLinkActor : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	AFaceLiveLinkActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bDisabled = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	FName LiveLinkSubjectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	FFaceSmoothParams SmoothParams{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bSmoothEnabled = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bPublishHeadRotation = true;
	
protected:
	TSharedPtr<IFaceDataPostProcessor> GetSmoothProcessor();
	bool WriteBlendShapeWeights(const FARBlendShapeMap& Weights) const;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void AddLiveLinkSource();
	void RemoveLiveLinkSource();
	TSharedPtr<IFaceLinkLinkSource> Source;
	TSharedPtr<IFaceDataPostProcessor> SmoothProcessor;
public:
	virtual void Tick(float DeltaTime) override;
private:
	FCriticalSection LiveLinkSourceLock;
};
