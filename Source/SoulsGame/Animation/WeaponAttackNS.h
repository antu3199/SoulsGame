// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "WeaponAttackNS.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API UWeaponAttackNS : public UAnimNotifyState
{
	GENERATED_BODY()

    virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
    
};
