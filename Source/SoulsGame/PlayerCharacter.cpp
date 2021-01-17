// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"


APlayerCharacter::APlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // You can do it this way, but I want to do it less segmentedly.
    //PlayerInputComponent->BindAxis(TEXT("RotateCamera"), this, &APlayerCharacter::RotateCamera);
    //PlayerInputComponent->BindAxis(TEXT("ChangePitch"), this, &APlayerCharacter::ChangePitch);
}


void APlayerCharacter::DoMeleeAttack()
{
    if (!this->CanUseAnyAbility())
    {
        return;
    }

    if (this->AbilitySystemComponent->IsUsingAbilityWithTag("Ability.Melee"))
    {
        return;
    }

    

    
     // AbilitySystemComponent->Get
    
}