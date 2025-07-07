// Copyright Epic Games, Inc. All Rights Reserved.

#include "TofuSurviveGameMode.h"
#include "TofuSurvivePlayerController.h"
#include "TofuSurviveCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATofuSurviveGameMode::ATofuSurviveGameMode()
{
	PlayerControllerClass = ATofuSurvivePlayerController::StaticClass();
	DefaultPawnClass = ATofuSurviveCharacter::StaticClass();
}