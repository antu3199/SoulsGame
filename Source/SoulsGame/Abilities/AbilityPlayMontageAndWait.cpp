// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityPlayMontageAndWait.h"


#include "PlayMontageAndWaitTask.h"
#include "Abilities/Tasks/AbilityTask.h"

void UAbilityPlayMontageAndWait::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                 const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    UE_LOG(LogTemp, Warning, TEXT("UAbilityPlayMontageAndWait::ActivateAbility!"));

    const FName TaskName = "Task Name";
    UPlayMontageAndWaitTask *PlayMontageAndWaitTask = UAbilityTask::NewAbilityTask<UPlayMontageAndWaitTask>(this, TaskName);
    PlayMontageAndWaitTask->OnCompleted.AddDynamic(this, &UAbilityPlayMontageAndWait::OnMontageCompleted);
    PlayMontageAndWaitTask->ReadyForActivation();
}

void UAbilityPlayMontageAndWait::EndAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UAbilityPlayMontageAndWait::OnMontageCompleted(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
    UE_LOG(LogTemp, Warning, TEXT("OnMontage Completed %s"), *GameplayTag.ToString());
}
