// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameplayAbility.h"

#include "GameplayTask.h"

TArray<FActiveGameplayEffectHandle> UMyGameplayAbility::ApplyGameplayEffectSpecToTarget(
    const FGameplayEffectSpecHandle EffectSpecHandle, FGameplayAbilityTargetDataHandle TargetData)
{
    return K2_ApplyGameplayEffectSpecToTarget(EffectSpecHandle, TargetData);
}

FGameplayEffectData& UMyGameplayAbility::InitializeGameplayEffectData(FGameplayEffectDataContainer& EffectsContainer,
    TSubclassOf<UMyGameplayEffect>& Effect) const
{
    FGameplayEffectData & Container = EffectsContainer.CreateNewGameplayEffectData();
    Container.GameplayEffect = Effect.GetDefaultObject();
    Container.GameplayEffectSpecHandle = MakeOutgoingGameplayEffectSpec(Effect, 1);
    
    return Container;
}

void UMyGameplayAbility::ApplyEffectsToActors(TArray<AActor*> &Actors)
{
    const TArray<FHitResult> HitResults;

    for (FGameplayEffectData & Data : this->GameplayEffectsContainer.ActiveGameplayEffects)
    {
        Data.AddTargets(HitResults, Actors);
        Data.ApplyEffect();
    }
}

/*
void UMyGameplayAbility::OnGameplayTaskActivated(UGameplayTask& Task)
{
    Super::OnGameplayTaskActivated(Task);
    UE_LOG(LogTemp, Warning, TEXT("Gameplay ability activated!"));
}
*/
void UMyGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    
}

void UMyGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMyGameplayAbility::InitializeEffectContainerHelper()
{
    for (TSubclassOf<UMyGameplayEffect> & Effect : this->AppliedGameplayEffects)
    {
        InitializeGameplayEffectData(this->GameplayEffectsContainer, Effect);
    }
}

