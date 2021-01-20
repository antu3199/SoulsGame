// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityMeleeBase.h"


#include "PlayMontageAndWaitTask.h"
#include "Abilities/Tasks/AbilityTask.h"

void UAbilityMeleeBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                 const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    UE_LOG(LogTemp, Warning, TEXT("UAbilityMeleeBase::ActivateAbility!"));
    
    if (this->CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        const FName TaskName = "Task Name";
        UPlayMontageAndWaitTask *PlayMontageAndWaitTask = UAbilityTask::NewAbilityTask<UPlayMontageAndWaitTask>(this, TaskName);
        PlayMontageAndWaitTask->OnCompleted.AddDynamic(this, &UAbilityMeleeBase::OnMontageCompleted);
        PlayMontageAndWaitTask->ReadyForActivation();
    }
}

void UAbilityMeleeBase::EndAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UAbilityMeleeBase::OnMontageCompleted(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
    UE_LOG(LogTemp, Warning, TEXT("OnMontage Completed %s"), *GameplayTag.ToString());
    this->EndAbility(this->CurrentSpecHandle, this->CurrentActorInfo, this->CurrentActivationInfo, true, false);
}
