// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayMontageAbility.h"

#include "PlayMontageAndWaitTask.h"
#include "Abilities/Tasks/AbilityTask.h"

#include "GameplayTagsManager.h"
#include "SoulsGame/CharacterBase.h"


void UPlayMontageAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    this->GameplayEffectsContainer.ActiveGameplayEffects.Reset();

    
    if (this->CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        if (this->PlayMontageAndWaitTaskData.OwningAbility == nullptr)
        {
            this->PlayMontageAndWaitTaskData.OwningAbility = this;
        }

        
        PlayMontageAndWaitTask = UPlayMontageAndWaitTask::CreatePlayMontageAndWaitEvent(this->PlayMontageAndWaitTaskData);
        
        PlayMontageAndWaitTask->OnCompleted.AddDynamic(this, &UPlayMontageAbility::OnCompleted);
        PlayMontageAndWaitTask->OnBlendOut.AddDynamic(this, &UPlayMontageAbility::OnBlendOut);
        PlayMontageAndWaitTask->OnInterrupted.AddDynamic(this, &UPlayMontageAbility::OnInterrupted);
        PlayMontageAndWaitTask->OnCancelled.AddDynamic(this, &UPlayMontageAbility::OnCancelled);
        PlayMontageAndWaitTask->OnEventReceived.AddDynamic(this, &UPlayMontageAbility::OnEventReceived);
        
        PlayMontageAndWaitTask->ReadyForActivation();
    }
}

void UPlayMontageAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UPlayMontageAbility::OnBlendOut(const FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
    this->EndAbility(this->CurrentSpecHandle, this->CurrentActorInfo, this->CurrentActivationInfo, true, false);
}

void UPlayMontageAbility::OnInterrupted(const FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
    this->EndAbility(this->CurrentSpecHandle, this->CurrentActorInfo, this->CurrentActivationInfo, true, true);
}

void UPlayMontageAbility::OnCancelled(const FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
    this->EndAbility(this->CurrentSpecHandle, this->CurrentActorInfo, this->CurrentActivationInfo, true, true);
}

void UPlayMontageAbility::OnCompleted(const FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
    // Don't want to do anything here
    //this->EndAbility(this->CurrentSpecHandle, this->CurrentActorInfo, this->CurrentActivationInfo, true, false);
}

void UPlayMontageAbility::OnEventReceived(const FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
    this->InitializeEffectContainerHelper();
}




