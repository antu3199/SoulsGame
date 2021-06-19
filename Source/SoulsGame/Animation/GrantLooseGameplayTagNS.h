// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAnimNotifyState.h"
#include "GrantLooseGameplayTagNS.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API UGrantLooseGameplayTagNS : public UMyAnimNotifyState
{
	GENERATED_BODY()

protected:
	virtual void DoNotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration);

	virtual void DoNotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation);
	
};
