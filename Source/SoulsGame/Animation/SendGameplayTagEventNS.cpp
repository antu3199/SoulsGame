// Fill out your copyright notice in the Description page of Project Settings.


#include "SendGameplayTagEventNS.h"

#include "AbilitySystemBlueprintLibrary.h"

void USendGameplayTagEventNS::DoNotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                          float TotalDuration)
{
	Super::DoNotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp == nullptr)
	{
		return;
	}

	if (MeshComp->GetOwner() == nullptr)
	{
	    return;
	}

	if (!Data.GameplayTag.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("ERROR: Gameplay tag not valid"));
		return;
	}

	AActor * Actor = MeshComp->GetOwner();
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Actor, Data.GameplayTag, FGameplayEventData());



}
