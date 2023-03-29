// Fill out your copyright notice in the Description page of Project Settings.


#include "UdpReceiver.h"

// Sets default values
AUdpReceiver::AUdpReceiver()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUdpReceiver::BeginPlay()
{
	Super::BeginPlay();

	this->Connect();

}

// Called every frame
void AUdpReceiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AUdpReceiver::EndPlay(const EEndPlayReason::Type EndPlayRreason)
{
	Super::EndPlay(EndPlayRreason);

	this->Close();
}

bool AUdpReceiver::Connect()
{
	if (m_Socket == NULL)
	{
		m_Socket = FUdpSocketBuilder(TEXT("UDP Socket"))
			.BoundToPort(this->_port)
			.Build();
	}

	if (m_Socket == NULL)
	{
		m_Receiver = new FUdpSocketReceiver(m_Socket, FTimespan(0, 0, 1), TEXT("UDP Receiver"));
		m_Receiver->OnDataReceived().BindUObject(this, &AUdpReceiver::UdpReceivedCallback);

		UE_LOG(LogTemp, Log, TEXT("Connected to UDP port %d"), this->_port); //接続成功
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("Could not open UDP port &d"), this->_port);
	return false;
}

void AUdpReceiver::Close()
{
	if (m_Receiver != NULL)
	{
		m_Receiver->Exit();
		delete m_Receiver;
		m_Receiver = NULL;
	}

	if (m_Socket != NULL)
	{
		m_Socket->Close();
		delete m_Socket;
		m_Socket = NULL;
	}
}

void AUdpReceiver::UdpReceivedCallback(const FArrayReaderPtr& data, const FIPv4Endpoint&)
{
	uint32 receivedSize = data->GetAllocatedSize();
	UE_LOG(LogTemp, Log, TEXT("%d bytes received!"), receivedSize);
}

