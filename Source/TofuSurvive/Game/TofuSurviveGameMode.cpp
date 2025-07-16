// Copyright Epic Games, Inc. All Rights Reserved.

#include "TofuSurviveGameMode.h"
#include "../Controllers/TofuSurvivePlayerController.h"
#include "../Characters/TofuSurviveCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATofuSurviveGameMode::ATofuSurviveGameMode()
{
	PlayerControllerClass = ATofuSurvivePlayerController::StaticClass();
	DefaultPawnClass = ATofuSurviveCharacter::StaticClass();
}