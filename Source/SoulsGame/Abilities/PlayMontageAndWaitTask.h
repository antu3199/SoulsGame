// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "SoulsGame/CharacterAbilitySystemComponent.h"

#include "PlayMontageAndWaitTask.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayMontageAndWaitTaskDelegate, FGameplayTag, varNameFGameplayTag, FGameplayEventData, varNameFGameplayEventData);

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
