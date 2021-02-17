// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySelfCast.h"

void UAbilitySelfCast::OnEventReceived(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
	Super::OnEventReceived(GameplayTag, GameplayEventData);
	const TArray<AActor*> HitActors{ GetOwningActorFromActorInfo() };
	const TArray<FHitResult> HitResults;

	for (FGameplayEffectData & Data : this->GameplayEffectsContainer.ActiveGameplayEffects)
	{
		Data.AddTargets(HitResults, HitActors);
		Data.ApplyEffect();
	}
}
