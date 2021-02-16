// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityMeleeBase.h"
#include "SoulsGame/CharacterBase.h"

void UAbilityMeleeBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UE_LOG(LogTemp, Warning, TEXT("UAbilityMeleeBase::ActivateAbility"));
	PlayMontageAndWaitTask->OnEventReceived.AddDynamic(this, &UAbilityMeleeBase::OnEventReceived);
}

void UAbilityMeleeBase::OnEventReceived(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
	Super::OnEventReceived(GameplayTag, GameplayEventData);
	UE_LOG(LogTemp, Warning, TEXT("UAbilityMeleeBase::OnEventReceived"));
	
	AActor * OwningActor = GetOwningActorFromActorInfo();
	ACharacterBase * OwningCharacter = Cast<ACharacterBase>(OwningActor);
	AActor * AvatarActor = GetAvatarActorFromActorInfo();
	
	// Get Target data
	TArray<FHitResult> HitResults;
	TArray<AActor *> TargetActors;
	UMyGameplayEffect::GetTargets_UseEventData(OwningCharacter, AvatarActor, GameplayEventData, HitResults, TargetActors);
	
	for (FGameplayEffectData & Container : this->GameplayEffectsContainer.ActiveGameplayEffects)
	{
		Container.AddTargets(HitResults, TargetActors);
		//Container.ApplyEffect();
		Container.ActiveGameplayEffectHandles = K2_ApplyGameplayEffectSpecToTarget(Container.GameplayEffectSpecHandle, Container.TargetData);
	}
}
