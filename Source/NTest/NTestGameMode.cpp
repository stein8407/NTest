// Copyright Epic Games, Inc. All Rights Reserved.

#include "NTestGameMode.h"
#include "NTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANTestGameMode::ANTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
