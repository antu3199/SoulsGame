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
