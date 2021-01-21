// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityMeleeBase.h"


#include "PlayMontageAndWaitTask.h"
#include "Abilities/Tasks/AbilityTask.h"
#include <functional>

void UAbilityMeleeBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                 const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    UE_LOG(LogTemp, Warning, TEXT("UAbilityMeleeBase::ActivateAbility!"));
    
    if (this->CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        if (this->PlayMontageAndWaitTaskData.OwningAbility == nullptr)
        {
            this->PlayMontageAndWaitTaskData.OwningAbility = this;
        }
        
        UPlayMontageAndWaitTask *PlayMontageAndWaitTask = UPlayMontageAndWaitTask::CreatePlayMontageAndWaitEvent(this->PlayMontageAndWaitTaskData);
        
        PlayMontageAndWaitTask->OnCompleted.AddDynamic(this, &UAbilityMeleeBase::OnCompleted);
        PlayMontageAndWaitTask->OnBlendOut.AddDynamic(this, &UAbilityMeleeBase::OnBlendOut);
        PlayMontageAndWaitTask->OnInterrupted.AddDynamic(this, &UAbilityMeleeBase::OnInterrupted);
        PlayMontageAndWaitTask->OnCancelled.AddDynamic(this, &UAbilityMeleeBase::OnCancelled);
        PlayMontageAndWaitTask->OnEventReceived.AddDynamic(this, &UAbilityMeleeBase::OnEventReceived);
        
        PlayMontageAndWaitTask->ReadyForActivation();
    }
}

void UAbilityMeleeBase::EndAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UAbilityMeleeBase::OnBlendOut(const FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
    UE_LOG(LogTemp, Warning, TEXT("OnBlendOut Completed %s"), *GameplayTag.ToString());
    this->EndAbility(this->CurrentSpecHandle, this->CurrentActorInfo, this->CurrentActivationInfo, true, false);
}

void UAbilityMeleeBase::OnInterrupted(const FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
    UE_LOG(LogTemp, Warning, TEXT("OnInterrupted Completed %s"), *GameplayTag.ToString());
    this->EndAbility(this->CurrentSpecHandle, this->CurrentActorInfo, this->CurrentActivationInfo, true, true);
}

void UAbilityMeleeBase::OnCancelled(const FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
    UE_LOG(LogTemp, Warning, TEXT("OnCancelled Completed %s"), *GameplayTag.ToString());
    this->EndAbility(this->CurrentSpecHandle, this->CurrentActorInfo, this->CurrentActivationInfo, true, true);
}

void UAbilityMeleeBase::OnCompleted(const FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
    UE_LOG(LogTemp, Warning, TEXT("OnCompleted Completed %s"), *GameplayTag.ToString());
    // Don't want to do anything here
    //this->EndAbility(this->CurrentSpecHandle, this->CurrentActorInfo, this->CurrentActivationInfo, true, false);
}

void UAbilityMeleeBase::OnEventReceived(const FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
    UE_LOG(LogTemp, Warning, TEXT("OnMontage Completed %s"), *GameplayTag.ToString());
    // TODO
}


