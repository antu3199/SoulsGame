// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAttackNS.h"



#include "GameplayTagsManager.h"
#include "SoulsGame/CharacterBase.h"
#include "SoulsGame/DataAssets/WeaponAsset.h"
#include "SoulsGame/Weapon/WeaponActor.h"

void UWeaponAttackNS::DoNotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    Super::DoNotifyBegin(MeshComp, Animation, TotalDuration);
    
    if (MeshComp == nullptr)
    {
        return;
    }
    
    ACharacterBase * Character = Cast<ACharacterBase>(MeshComp->GetOwner());
    if (Character == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("ERROR: No character!"));
        return;
    }
    
    AWeaponActor * WeaponActor = Character->WeaponActor;
    if (!WeaponActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("ERROR: No weapon actor!"));
        return;
    }

    // TODO: Expose this
    const FGameplayTag EventTag = Data.GameplayTag;
    WeaponActor->BeginWeaponAttack(EventTag);
}

void UWeaponAttackNS::DoNotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::DoNotifyEnd(MeshComp, Animation);

    if (MeshComp == nullptr)
    {
        return;
    }

    ACharacterBase * Character = Cast<ACharacterBase>(MeshComp->GetOwner());
    if (Character == nullptr)
    {
        return;
    }
    
    AWeaponActor * WeaponActor = Character->WeaponActor;
    if (!WeaponActor)
    {
        return;
    }

    WeaponActor->EndWeaponAttack();
}
