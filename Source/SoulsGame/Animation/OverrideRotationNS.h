// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAnimNotifyState.h"
#include "OverrideRotationNS.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API UOverrideRotationNS : public UMyAnimNotifyState
{
	GENERATED_BODY()

protected:
	virtual void DoNotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;

	virtual void DoNotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;

};
