// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CharacterAbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class SOULSGAME_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

	UPROPERTY(EditAnywhere)
	int32 TestInt;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UCharacterAbilitySystemComponent* AbilitySystemComponent;

    bool IsDead;

	float AnimMovementSpeed;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	bool GetIsDead() const;
	
	//UPROPERTY(BlueprintReadWrite)
	//float Speed;

   // Animation blueprint property
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe)) // Needs to be BlueprintThreadSafe otherwise warning in ABP
	float GetAnimMovementSpeed() const;

	UFUNCTION(BlueprintCallable)
    void UpdateAnimMovementSpeed();
	
	
};
