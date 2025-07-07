// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "TofuSurvivePlayerController.generated.h"

/** Forward declaration to improve compiling times */
struct FInputActionValue;
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class ATofuSurvivePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATofuSurvivePlayerController();

	// /** Time Threshold to know if it was a short press */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	// float ShortPressThreshold;
	//
	// /** FX Class that we will spawn when clicking */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	// UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SkillAction;
	//
	// /** Jump Input Action */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	// UInputAction* SetDestinationClickAction;
	//
	// /** Jump Input Action */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	// UInputAction* SetDestinationTouchAction;

protected:
	// /** True if the controlled character should navigate to the mouse cursor. */
	// uint32 bMoveToMouseCursor : 1;

	FVector CachedMoveInput;
	bool bSkillReady;
	float SkillCooldownTimer;
	
	virtual void SetupInputComponent() override;

	
	
	// To add mapping context
	virtual void BeginPlay() override;

	void OnMove(const FInputActionValue& Value);
	void OnSkill(const FInputActionValue& Value);
	
	// /** Input handlers for SetDestination action. */
	// void OnInputStarted();
	// void OnSetDestinationTriggered();
	// void OnSetDestinationReleased();
	// void OnTouchTriggered();
	// void OnTouchReleased();

private:
	// FVector CachedDestination;
	//
	// bool bIsTouch; // Is it a touch device
	// float FollowTime; // For how long it has been pressed
};


