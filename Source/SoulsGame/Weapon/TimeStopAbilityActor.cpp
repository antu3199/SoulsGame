// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeStopAbilityActor.h"

#include "GameplayTagsManager.h"
#include "SoulsGame/CharacterBase.h"
#include "SoulsGame/Abilities/Tasks/AsyncTaskTagChanged.h"

ATimeStopAbilityActor::ATimeStopAbilityActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ATimeStopAbilityActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ACharacterBase *CharacterBase = Cast<ACharacterBase>(OtherActor);
	if (CharacterBase == nullptr || this->Ability == nullptr)
	{
		return;
	}

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



void ATimeStopAbilityActor::OnTagAdded(const FGameplayTag CooldownTag, int32 NewCount)
{
	UE_LOG(LogTemp, Warning, TEXT("STUNNNNN"));
}

void ATimeStopAbilityActor::OnTagRemoved(const FGameplayTag CooldownTag, int32 NewCount)
{
	UE_LOG(LogTemp, Warning, TEXT("END STUN"));
}
