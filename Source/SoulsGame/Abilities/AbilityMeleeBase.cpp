// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityMeleeBase.h"
#include "SoulsGame/CharacterBase.h"

void UAbilityMeleeBase::OnEventReceived(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
	Super::OnEventReceived(GameplayTag, GameplayEventData);
	
	AActor * OwningActor = GetOwningActorFromActorInfo();
	ACharacterBase * OwningCharacter = Cast<ACharacterBase>(OwningActor);
	AActor * AvatarActor = GetAvatarActorFromActorInfo();
	
	// Get Target data
	TArray<FHitResult> HitResults;
	TArray<AActor *> TargetActors;
	UMyGameplayEffect::GetTargets_UseEventData(OwningCharacter, AvatarActor, GameplayEventData, HitResults, TargetActors);
	
	for (TSubclassOf<UMyGameplayEffect> & Effect : this->AppliedGameplayEffects)
	{
		int level = 1;

		// Bind Ability to effect
		FGameplayEffectData & Container = this->GameplayEffectsContainer.CreateNewGameplayEffectData();
		Container.GameplayEffect = Effect.GetDefaultObject();
		Container.GameplayEffectSpecHandle = MakeOutgoingGameplayEffectSpec(Effect, 1);

		Container.AddTargets(HitResults, TargetActors);
        
		Container.ActiveGameplayEffectHandles = K2_ApplyGameplayEffectSpecToTarget(Container.GameplayEffectSpecHandle, Container.TargetData);
	}


}
