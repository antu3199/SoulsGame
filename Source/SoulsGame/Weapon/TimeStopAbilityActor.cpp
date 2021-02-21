// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeStopAbilityActor.h"

#include "GameplayTagsManager.h"
#include "SoulsGame/CharacterBase.h"
#include "SoulsGame/Abilities/Tasks/AsyncTaskTagChanged.h"

ATimeStopAbilityActor::ATimeStopAbilityActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ATimeStopAbilityActor::Initialize(UMyGameplayAbility* DataContainer)
{
	Super::Initialize(DataContainer);

	// Allow immediately overlapping actors to trigger
	TArray<AActor *> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor *& Actor : OverlappingActors)
	{
		this->NotifyActorBeginOverlap(Actor);
	}
}

void ATimeStopAbilityActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);


	
	ACharacterBase *CharacterBase = Cast<ACharacterBase>(OtherActor);
	if (CharacterBase == nullptr || this->Ability == nullptr)
	{
		return;
	}

	if (HitActors.Contains(OtherActor))
	{
		return;
	}

	HitActors.Add(OtherActor);

	UE_LOG(LogTemp, Warning, TEXT("Apply timestop to: %s"), *OtherActor->GetName());


	TArray<AActor *> OverlappingActors {OtherActor};

	FAsyncTaskTagChangedData TaskData;
	TaskData.AbilitySystemComponent = CharacterBase->GetAbilitySystemComponent();
	TaskData.EffectGameplayTag = UGameplayTagsManager::Get().RequestGameplayTag(TEXT("State.Timestopped"));
	TaskData.DestroyOnZero = true;

	UAsyncTaskTagChanged * TagChangedTask = UAsyncTaskTagChanged::CreateTagChangedTask(TaskData);
	TagChangedTask->OnTagAdded.AddDynamic(this, &ATimeStopAbilityActor::OnTagAdded);
	TagChangedTask->OnTagRemoved.AddDynamic(this, &ATimeStopAbilityActor::OnTagRemoved);

	TagChangedTask->Activate();


	this->Ability->ApplyEffectsToActors(OverlappingActors);




}

void ATimeStopAbilityActor::NotifyActorEndOverlap(AActor* OtherActor)
{

	Super::NotifyActorEndOverlap(OtherActor);
	
	ACharacterBase *CharacterBase = Cast<ACharacterBase>(OtherActor);
	if (CharacterBase == nullptr || this->Ability == nullptr)
	{
		return;
	}

	if (HitActors.Contains(OtherActor))
	{
		HitActors.Remove(OtherActor);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("End overlap called in a non hit actor??"));
	}

	UAbilitySystemComponent * AbilitySystemComponent = CharacterBase->GetAbilitySystemComponent();
	TArray<AActor *> OverlappingActors {OtherActor};
	for (auto EffectSpec : this->Ability->GameplayEffectsContainer.ActiveGameplayEffects)
	{
		for (auto &ActiveHandle : EffectSpec.ActiveGameplayEffectHandles)
		{
			AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveHandle);
		}
	}
}


void ATimeStopAbilityActor::OnTagAdded(const FGameplayTag CooldownTag, int32 NewCount)
{
	UE_LOG(LogTemp, Warning, TEXT("STUNNNNN"));
}

void ATimeStopAbilityActor::OnTagRemoved(const FGameplayTag CooldownTag, int32 NewCount)
{
	UE_LOG(LogTemp, Warning, TEXT("END STUN"));
}
