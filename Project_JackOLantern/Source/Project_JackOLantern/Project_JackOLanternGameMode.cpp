// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_JackOLanternGameMode.h"
#include "Project_JackOLanternCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_JackOLanternGameMode::AProject_JackOLanternGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
