// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAnimNotifyState.h"
#include "SendGameplayTagEventNS.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API USendGameplayTagEventNS : public UMyAnimNotifyState
{
	GENERATED_BODY()
	
protected:
	virtual void DoNotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
};
