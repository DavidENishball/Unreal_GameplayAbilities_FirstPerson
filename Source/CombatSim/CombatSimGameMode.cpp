// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CombatSimGameMode.h"
#include "CombatSimHUD.h"
#include "CombatSimCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACombatSimGameMode::ACombatSimGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACombatSimHUD::StaticClass();
}
