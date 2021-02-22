// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MyAnimNotifyState.generated.h"

USTRUCT(BlueprintType)
struct FAnimNotifyData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTag GameplayTag;
};

/**
 * 
 */
UCLASS()
class SOULSGAME_API UMyAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	


public:
	UPROPERTY(EditAnywhere)
	FAnimNotifyData Data;

protected:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;

	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;


	virtual void DoNotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration);

	bool HasTriggered = false;
};
