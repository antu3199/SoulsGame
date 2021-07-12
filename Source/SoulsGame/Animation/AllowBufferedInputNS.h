// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAnimNotifyState.h"
#include "AllowBufferedInputNS.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API UAllowBufferedInputNS : public UMyAnimNotifyState
{
	GENERATED_BODY()
	
protected:
	virtual void DoNotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	virtual void DoNotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;
};
