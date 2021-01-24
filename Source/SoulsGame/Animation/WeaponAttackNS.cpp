// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAttackNS.h"


#include "SoulsGame/CharacterBase.h"
#include "SoulsGame/DataAssets/WeaponAsset.h"
#include "SoulsGame/Weapon/WeaponActor.h"

void UWeaponAttackNS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
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
    
    UWeaponAsset * WeaponAsset = Character->GetWeaponAsset();
    if (!WeaponAsset)
    {
        UE_LOG(LogTemp, Warning, TEXT("ERROR: No weapon asset!"));
        return;
    }

    AWeaponActor * WeaponActor = Cast<AWeaponActor>(WeaponAsset->WeaponActor->GetDefaultObject());
    if (!WeaponActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("ERROR: No weapon actor!"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Attack triggered NS"));

    const FGameplayTag DummyTag;
    WeaponActor->BeginWeaponAttack(DummyTag);
}
