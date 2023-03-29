// Fill out your copyright notice in the Description page of Project Settings.


#include "test.h"
#include "unreal_dev/Public/test.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values
Atest::Atest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Atest::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void Atest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UKismetSystemLibrary::PrintString(GEngine->GetWorld(), "test");
	
}

