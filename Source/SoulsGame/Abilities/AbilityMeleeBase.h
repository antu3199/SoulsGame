// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PlayMontageAbility.h"
#include "AbilityMeleeBase.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API UAbilityMeleeBase : public UPlayMontageAbility
{
	GENERATED_BODY()
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void OnEventReceived(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData) override;
};
