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
	
protected:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;

public:
	UPROPERTY(EditAnywhere)
	FAnimNotifyData Data;
};
