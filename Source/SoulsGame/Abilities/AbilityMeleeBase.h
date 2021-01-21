// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PlayMontageAndWaitTask.h"
#include "SoulsGame/MyGameplayAbility.h"
#include "AbilityMeleeBase.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API UAbilityMeleeBase : public UMyGameplayAbility
{
	GENERATED_BODY()

protected:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void OnBlendOut(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData);
	virtual void OnInterrupted(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData);
	virtual void OnCancelled(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData);
	virtual void OnCompleted(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData);
	virtual void OnEventReceived(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData);

	UPROPERTY(EditAnywhere)
	FPlayMontageAndWaitTaskData PlayMontageAndWaitTaskData;
};
