// Fill out your copyright notice in the Description page of Project Settings.


#include "GrantLooseGameplayTagNS.h"

void UGrantLooseGameplayTagNS::DoNotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
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

	ACharacterBase *Character = Cast<ACharacterBase>(MeshComp->GetOwner());
	if (Character == nullptr)
	{
		return;
	}

	Character->GetAbilitySystemComponent()->AddLooseGameplayTag(Data.GameplayTag);
}

void UGrantLooseGameplayTagNS::DoNotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::DoNotifyEnd(MeshComp, Animation);

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

	ACharacterBase *Character = Cast<ACharacterBase>(MeshComp->GetOwner());
	if (Character == nullptr)
	{
		return;
	}

	Character->GetAbilitySystemComponent()->RemoveLooseGameplayTag(Data.GameplayTag);
}
