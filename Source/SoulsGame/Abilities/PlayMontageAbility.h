// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyGameplayAbility.h"
#include "PlayMontageAndWaitTask.h"

#include "PlayMontageAbility.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API UPlayMontageAbility : public UMyGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	// Callbacks (Must be a UPROPERTY() otherwise error)
	UFUNCTION()
    virtual void OnBlendOut(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData);
	UFUNCTION()
    virtual void OnInterrupted(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData);
	UFUNCTION()
    virtual void OnCancelled(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData);
	UFUNCTION()
    virtual void OnCompleted(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData);
	UFUNCTION()
    virtual void OnEventReceived(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData);

	UPROPERTY(EditAnywhere)
	FPlayMontageAndWaitTaskData PlayMontageAndWaitTaskData;

	UPROPERTY()
	UPlayMontageAndWaitTask * PlayMontageAndWaitTask;
	
};
