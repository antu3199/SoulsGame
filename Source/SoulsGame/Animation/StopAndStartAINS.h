// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAnimNotifyState.h"
#include "StopAndStartAINS.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API UStopAndStartAINS : public UMyAnimNotifyState
{
	GENERATED_BODY()

	virtual void DoNotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;

	virtual void DoNotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;
	
};
