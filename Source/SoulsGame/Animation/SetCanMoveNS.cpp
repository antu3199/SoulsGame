// Fill out your copyright notice in the Description page of Project Settings.


#include "SetCanMoveNS.h"

void USetCanMoveNS::DoNotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::DoNotifyBegin(MeshComp, Animation, TotalDuration);
	
	ACharacterBase * Character = GetCharacter(MeshComp);

	if (Character == nullptr)
	{
		return;
	}

	Character->SetCanMove(CanMoveNotifyStart);
}

void USetCanMoveNS::DoNotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::DoNotifyEnd(MeshComp, Animation);
	
	ACharacterBase * Character = GetCharacter(MeshComp);

	if (Character == nullptr)
	{
		return;
	}

	Character->SetCanMove(CanMoveNotifyEnd);
}
