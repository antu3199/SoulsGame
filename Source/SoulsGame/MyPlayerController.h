// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void UpdateRotation(float DeltaTime) override;

	// Called to bind functionality to input

	virtual void SetupInputComponent() override;

	void HandleCameraRotation();

	void RotateCamera(float InputAxis);
	void MoveForward(float InputAxis);
	void MoveRight(float InputAxis);
	
	void NormalAttack();

	void UseAbility();


	APlayerCharacter * GetPawnCharacter() const;
};
