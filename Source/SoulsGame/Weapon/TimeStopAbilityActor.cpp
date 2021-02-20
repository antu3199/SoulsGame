// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeStopAbilityActor.h"
#include "SoulsGame/CharacterBase.h"
#include "SoulsGame/Abilities/Tasks/AsyncTaskEffectStackChanged.h"

ATimeStopAbilityActor::ATimeStopAbilityActor()
{
	PrimaryActorTick.bCanEverTick = true;

}



void ATimeStopAbilityActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// TODO: Change size

	TArray<AActor *> OverlappingActors;
	this->GetOverlappingActors(OverlappingActors);



	for (AActor * Actor : OverlappingActors)
	{
		ACharacterBase *CharacterBase = Cast<ACharacterBase>(Actor);
		if (!CharacterBase)
		{
			continue;
		}
		
		//FAsyncTaskEffectStackChangedData TaskData;
		///TaskData.AbilitySystemComponent = CharacterBase->GetAbilitySystemComponent();
		//TaskData.EffectGameplayTag = UGameplayTagsManager::Get().RequestGameplayTag(TEXT("State."));

		
		//UAsyncTaskEffectStackChanged StackChangedTask = UAsyncTaskEffectStackChanged::CreateGameplayEffectStackChanged();
		

	}
	this->Ability->ApplyEffectsToActors(OverlappingActors);

	
	
	
}
