// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "MyAssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


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

    UAnimInstance * AnimInstance = GetMesh()->GetAnimInstance();
    if (!AnimInstance)
    {
        //UE_LOG(LogTemp, Display, TEXT("No anim instance!"));
    }

    UAnimMontage * CurrentActiveMontage = AnimInstance->GetCurrentActiveMontage();
    if (!CurrentActiveMontage)
    {
        UE_LOG(LogTemp, Display, TEXT("No current montage!"));
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("YES current montage!"));
    }
    

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
    if (!this->AbilitySystemComponent)
    {
        return;
    }
    
    if (!this->CanUseAnyAbility())
    {
        return;
    }


    const FName MeleeAbilityTag = "Ability.Melee";

    if (!this->AbilitySystemComponent->IsUsingAbilityWithTag(MeleeAbilityTag))
    {
        // Start melee ability
        this->AbilitySystemComponent->ActivateAbilityWithTag(MeleeAbilityTag);
    }
    else
    {
        this->BufferJumpSectionForCombo();
    }
}

void APlayerCharacter::DoOnRoll()
{
    if (!this->AbilitySystemComponent)
    {
        return;
    }
    
    if (!this->CanUseAnyAbility())
    {
        return;
    }

    if (this->OnRollMontage == nullptr)
    {
        return;
    }

    //FRotator ControlRotation = GetControlRotation(); // Control rotation is the camera, but I don't want this.
    //SetActorRotation(ControlRotation);
    

    //FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, Right);
    //    PawnCharacter->SetActorRotation(Rotation);

    
    UAnimInstance * AnimInstance = GetMesh()->GetAnimInstance();
    if (!AnimInstance)
    {
        return;
    }


    AnimInstance->Montage_Play(OnRollMontage);


}

bool APlayerCharacter::IsRootMotionDisabled() const
{
    UAnimInstance * AnimInstance = GetMesh()->GetAnimInstance();
    if (!AnimInstance)
    {
        return false;
    }

    FAnimMontageInstance* MontageInstance = AnimInstance->GetActiveMontageInstance();
    if (!MontageInstance)
    {
        return false;
    }

    if (MontageInstance->IsRootMotionDisabled())
    {
        return true;
    }

    return false;
}





