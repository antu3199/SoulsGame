// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameplayEffect.h"
#include "MyGameplayAbility.h"
#include "SoulsGame/CharacterBase.h"

// FGameplayEffectDataContainer ========================

void FGameplayEffectData::AddTargets(const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors)
{
    for (const FHitResult& HitResult : HitResults)
    {
        FGameplayAbilityTargetData_SingleTargetHit* NewData = new FGameplayAbilityTargetData_SingleTargetHit(HitResult);
        TargetData.Add(NewData);
    }

    if (TargetActors.Num() > 0)
    {
        FGameplayAbilityTargetData_ActorArray * NewData = new FGameplayAbilityTargetData_ActorArray();
        NewData->TargetActorArray.Append(TargetActors);
        TargetData.Add(NewData);
    }
}

void FGameplayEffectData::ApplyEffect()
{
    if (TargetData.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Warning: Effect has no targets!"));
        return;
    }
    
    FGameplayEffectSpecHandle & SpecHandle = GameplayEffectSpecHandle;
    if (SpecHandle.IsValid())
    {
        // Activate for each target in target data
        for (TSharedPtr<FGameplayAbilityTargetData> TData : TargetData.Data )
        {
            this->ActiveGameplayEffectHandles.Append(TData->ApplyGameplayEffectSpec(*SpecHandle.Data.Get()));
        }
    }

    // Another way to apply effect
    //Container.ActiveGameplayEffectHandles = K2_ApplyGameplayEffectSpecToTarget(Container.GameplayEffectSpecHandle, Container.TargetData);
}

FGameplayEffectData& FGameplayEffectDataContainer::CreateNewGameplayEffectData()
{
    this->ActiveGameplayEffects.Add(FGameplayEffectData());

    FGameplayEffectData & Container = this->ActiveGameplayEffects.Last();
    return Container;
}

bool FGameplayEffectDataContainer::DoesEffectContainerHaveEffects() const
{
    return ActiveGameplayEffects.Num() > 0;
}

// UMyGameplayEffect =======================
void UMyGameplayEffect::GetTargets_UseEventData(ACharacterBase* TargetingCharacter, AActor* TargetingActor,
                                                const FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors)
{
    const FHitResult * FoundHitResult = EventData.ContextHandle.GetHitResult();
    if (FoundHitResult)
    {
        OutHitResults.Add(*FoundHitResult);
    }
    else if (EventData.Target)
    {
        OutActors.Add(const_cast<AActor*>(EventData.Target));
    }
}
