// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MyAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API UMyAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	
};
