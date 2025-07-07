// Copyright Epic Games, Inc. All Rights Reserved.

#include "TofuSurvivePlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "TofuSurviveCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ATofuSurvivePlayerController::ATofuSurvivePlayerController()
{
	DefaultMappingContext = nullptr;
	MoveAction = nullptr;
	SkillAction = nullptr;
	bSkillReady = false;
	SkillCooldownTimer = 0.f;
	// bShowMouseCursor = true;
	// DefaultMouseCursor = EMouseCursor::Default;
	// CachedDestination = FVector::ZeroVector;
	// FollowTime = 0.f;
}

void ATofuSurvivePlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	UE_LOG(LogTemplateCharacter, Warning, TEXT("ATofuSurvivePlayerController::BeginPlay"));

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ATofuSurvivePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// // Add Input Mapping Context
	// if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	// {
	// 	Subsystem->AddMappingContext(DefaultMappingContext, 0);
	// }

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		//Move
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATofuSurvivePlayerController::OnMove);
		//Skill
		EnhancedInputComponent->BindAction(SkillAction, ETriggerEvent::Started, this, &ATofuSurvivePlayerController::OnSkill);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("No Enhanced Input Component found in %s"), *GetNameSafe(this));
	}
	// // Set up action bindings
	// if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	// {
	// 	// Setup mouse input events
	// 	EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ATofuSurvivePlayerController::OnInputStarted);
	// 	EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ATofuSurvivePlayerController::OnSetDestinationTriggered);
	// 	EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ATofuSurvivePlayerController::OnSetDestinationReleased);
	// 	EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ATofuSurvivePlayerController::OnSetDestinationReleased);
	//
	// 	// Setup touch input events
	// 	EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ATofuSurvivePlayerController::OnInputStarted);
	// 	EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ATofuSurvivePlayerController::OnTouchTriggered);
	// 	EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ATofuSurvivePlayerController::OnTouchReleased);
	// 	EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ATofuSurvivePlayerController::OnTouchReleased);
	// }
	// else
	// {
	// 	UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	// }
}

void ATofuSurvivePlayerController::OnMove(const FInputActionValue &Value)
{
	FVector2D MoveValue = Value.Get<FVector2D>();
	UE_LOG(LogTemplateCharacter, Log, TEXT("Move Triggered X: %f"), MoveValue.X);
	UE_LOG(LogTemplateCharacter, Log, TEXT("Move Triggered Y: %f"), MoveValue.Y);

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(FVector::ForwardVector, MoveValue.Y);
		ControlledPawn->AddMovementInput(FVector::RightVector, MoveValue.X);
	}
}

void ATofuSurvivePlayerController::OnSkill(const FInputActionValue &Value)
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Skill 쿨타임"));

	if (bSkillReady)
	{
		UE_LOG(LogTemplateCharacter, Log, TEXT("Skill 사용"));
		bSkillReady = false;
		SkillCooldownTimer = 5.f;
	}
}

// void ATofuSurvivePlayerController::OnInputStarted()
// {
// 	StopMovement();
// }
//
// // Triggered every frame when the input is held down
// void ATofuSurvivePlayerController::OnSetDestinationTriggered()
// {
// 	// We flag that the input is being pressed
// 	FollowTime += GetWorld()->GetDeltaSeconds();
// 	
// 	// We look for the location in the world where the player has pressed the input
// 	FHitResult Hit;
// 	bool bHitSuccessful = false;
// 	if (bIsTouch)
// 	{
// 		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
// 	}
// 	else
// 	{
// 		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
// 	}
//
// 	// If we hit a surface, cache the location
// 	if (bHitSuccessful)
// 	{
// 		CachedDestination = Hit.Location;
// 	}
// 	
// 	// Move towards mouse pointer or touch
// 	APawn* ControlledPawn = GetPawn();
// 	if (ControlledPawn != nullptr)
// 	{
// 		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
// 		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
// 	}
// }

// void ATofuSurvivePlayerController::OnSetDestinationReleased()
// {
// 	// If it was a short press
// 	if (FollowTime <= ShortPressThreshold)
// 	{
// 		// We move there and spawn some particles
// 		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
// 		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
// 	}
//
// 	FollowTime = 0.f;
// }
//
// // Triggered every frame when the input is held down
// void ATofuSurvivePlayerController::OnTouchTriggered()
// {
// 	bIsTouch = true;
// 	OnSetDestinationTriggered();
// }
//
// void ATofuSurvivePlayerController::OnTouchReleased()
// {
// 	bIsTouch = false;
// 	OnSetDestinationReleased();
// }
