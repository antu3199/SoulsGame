// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "SoulsGame/CharacterAbilitySystemComponent.h"

#include "PlayMontageAndWaitTask.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayMontageAndWaitTaskDelegate, FGameplayTag, varNameFGameplayTag, FGameplayEventData, varNameFGameplayEventData);

USTRUCT(BlueprintType)
struct FPlayMontageAndWaitTaskData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName TaskInstanceName = "TaskName";
	UPROPERTY(EditAnywhere)
	UAnimMontage *MontageToPlay;
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer EventTags;
	UPROPERTY(EditAnywhere)
	float Rate = 1.0;
	UPROPERTY(EditAnywhere)
	FName StartSection = "None";
	UPROPERTY(EditAnywhere)
	bool StopWhenAbilityEnds = true;
	UPROPERTY(EditAnywhere)
	float AnimRootMotionTranslationScale = 1.0;
};

/**
 * 
 */
UCLASS()
class SOULSGAME_API UPlayMontageAndWaitTask : public UAbilityTask
{
	GENERATED_BODY()


public:
	UPlayMontageAndWaitTask(const FObjectInitializer & ObjectInitializer);


	// Callbacks:
	UPROPERTY(BlueprintAssignable)
	FPlayMontageAndWaitTaskDelegate OnCompleted;
	
protected:
	virtual void Activate() override;
	virtual void ExternalCancel() override;
	virtual void OnDestroy(bool AbilityEnded) override;

	UCharacterAbilitySystemComponent * GetTargetAbilitySystemComponent() const;

	
};
