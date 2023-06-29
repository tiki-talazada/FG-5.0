// Copyright Epic Games, Inc. All Rights Reserved.

#include "FGGameMode.h"
#include "FGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFGGameMode::AFGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
