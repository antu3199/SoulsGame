// Fill out your copyright notice in the Description page of Project Settings.


#include "OverrideRotationNS.h"

void UOverrideRotationNS::DoNotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::DoNotifyBegin(MeshComp, Animation, TotalDuration);

	ACharacterBase * Character = GetCharacter(MeshComp);
	if (!Character)
	{
		return;
	}

	Character->OverrideRotation = true;
}

void UOverrideRotationNS::DoNotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::DoNotifyEnd(MeshComp, Animation);

	ACharacterBase * Character = GetCharacter(MeshComp);
	if (!Character)
	{
		return;
	}

	Character->OverrideRotation = false;
}
