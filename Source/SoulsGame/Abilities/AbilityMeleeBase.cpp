// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityMeleeBase.h"


#include "PlayMontageAndWaitTask.h"
#include "Abilities/Tasks/AbilityTask.h"

#include "GameplayTagsManager.h"
#include "SoulsGame/CharacterBase.h"

UAbilityMeleeBase::UAbilityMeleeBase() : Super()
{
    const FGameplayTag Tag = UGameplayTagsManager::Get().RequestGameplayTag(TEXT("Ability.Melee"));
    this->AbilityTags.AddTag(Tag);
}

void UAbilityMeleeBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    
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

    this->ActiveGameplayEffects.Reset();
}

void UAbilityMeleeBase::OnBlendOut(const FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
    UE_LOG(LogTemp, Warning, TEXT("OnBlendOut %s"), *GameplayTag.ToString());
    this->EndAbility(this->CurrentSpecHandle, this->CurrentActorInfo, this->CurrentActivationInfo, true, false);
}

void UAbilityMeleeBase::OnInterrupted(const FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
    UE_LOG(LogTemp, Warning, TEXT("OnInterrupted %s"), *GameplayTag.ToString());
    this->EndAbility(this->CurrentSpecHandle, this->CurrentActorInfo, this->CurrentActivationInfo, true, true);
}

void UAbilityMeleeBase::OnCancelled(const FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
    UE_LOG(LogTemp, Warning, TEXT("OnCancelled %s"), *GameplayTag.ToString());
    this->EndAbility(this->CurrentSpecHandle, this->CurrentActorInfo, this->CurrentActivationInfo, true, true);
}

void UAbilityMeleeBase::OnCompleted(const FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
    UE_LOG(LogTemp, Warning, TEXT("OnCompleted %s"), *GameplayTag.ToString());
    // Don't want to do anything here
    //this->EndAbility(this->CurrentSpecHandle, this->CurrentActorInfo, this->CurrentActivationInfo, true, false);
}

void UAbilityMeleeBase::OnEventReceived(const FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
    //this->CurrentActorInfo->AbilitySystemComponent->ApplyGameplayEffectSpecToTarget
    AActor * OwningActor = GetOwningActorFromActorInfo();
    ACharacterBase * OwningCharacter = Cast<ACharacterBase>(OwningActor);
    AActor * AvatarActor = GetAvatarActorFromActorInfo();
    
    // TODO Make my own gamepaly effect class & a struct for handlers
    for (TSubclassOf<UMyGameplayEffect> & Effect : this->AppliedGameplayEffects)
    {
        int level = 1;
        this->ActiveGameplayEffects.Add(FGameplayEffectDataContainer());
        FGameplayEffectDataContainer & Container = this->ActiveGameplayEffects.Last();
        Container.GameplayEffect = Effect.GetDefaultObject();
        Container.GameplayEffectSpecHandle = MakeOutgoingGameplayEffectSpec(Effect, 1);

        // Get Target data
        TArray<FHitResult> HitResults;
        TArray<AActor *> TargetActors;
        UMyGameplayEffect::GetTargets_UseEventData(OwningCharacter, AvatarActor, GameplayEventData, HitResults, TargetActors);
        Container.AddTargets(HitResults, TargetActors);
        
        Container.ActiveGameplayEffectHandles = K2_ApplyGameplayEffectSpecToTarget(Container.GameplayEffectSpecHandle, Container.TargetData);
        
    }
}


