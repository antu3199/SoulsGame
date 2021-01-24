// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "MyAssetManager.h"


APlayerCharacter::APlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    this->MakeWeapon();

    
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
    if (!this->AbilitySystemComponent)
    {
        return;
    }
    
    if (!this->CanUseAnyAbility())
    {
        return;
    }


    const FName MeleeAbilityTag = "Ability.Melee";

    if (this->AbilitySystemComponent->IsUsingAbilityWithTag(MeleeAbilityTag))
    {
        return;
    }
    
    if (this->AbilitySystemComponent->ActivateAbilityWithTag(MeleeAbilityTag))
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter::DoMeleeAttack SUCCESSED!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter::DoMeleeAttack FAILED"));
    }
}

void APlayerCharacter::MakeWeapon()
{
    if (this->WeaponAsset == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("No weapon found!"));
        return;
    }
    const FRotator Rotation = FRotator::ZeroRotator;
    const FVector Location(0, 0, -1000);
    const FVector Scale = FVector::OneVector;
    const FTransform Transform(Rotation,Location, Scale);
    FActorSpawnParameters SpawnParameters;
    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined; //Default

    AActor * SpawnedObject = GetWorld()->SpawnActor<AActor>(this->WeaponAsset->WeaponActor, Location, Rotation, SpawnParameters);
    if (SpawnedObject)
    {
       //this->AttachToComponent(this->GetMesh(), SpawnedObject,
       const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true );
       const FName SocketName = "hand_rSocket";
       SpawnedObject->AttachToComponent(this->GetMesh(), AttachmentRules, SocketName);
    }
}
