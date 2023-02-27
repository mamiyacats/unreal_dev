// Copyright Epic Games, Inc. All Rights Reserved.

#include "unreal_devGameMode.h"
#include "unreal_devCharacter.h"
#include "UObject/ConstructorHelpers.h"

Aunreal_devGameMode::Aunreal_devGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
