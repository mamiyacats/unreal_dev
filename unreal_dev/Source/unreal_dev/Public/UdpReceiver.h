// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Networking.h"
#include "Sockets.h"

#include "UdpReceiver.generated.h"

UCLASS()
class UNREAL_DEV_API AUdpReceiver : public AActor
{
	GENERATED_BODY() //最初に固定

	FSocket* m_Socket;
	FUdpSocketReceiver* m_Receiver;

	void UdpReceivedCallback(const FArrayReaderPtr& data, const FIPv4Endpoint& ip); //Udpが届いた際に呼ばれるコールバック


public:
	// Sets default values for this actor's properties
	AUdpReceiver();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDP") int32 _port = 7001; //Udp待ち受けポート番号
	UFUNCTION(BlueprintCallable, Category = "UDP") bool Connect(); //ポートを開いて受信待ち状態にする。
	UFUNCTION(BlueprintCallable, Category = "UDP") void Close(); //ポートを閉じて通信終了する。

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayRreason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
