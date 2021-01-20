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

	void OnMontageCompleted(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData);

	UPROPERTY(EditAnywhere)
	FPlayMontageAndWaitTaskData PlayMontageAndWaitTaskData;
	
};
