// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerJumpSectionNS.h"

void UTriggerJumpSectionNS::DoNotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::DoNotifyBegin(MeshComp, Animation, TotalDuration);

	ACharacterBase * Character = GetCharacter(MeshComp);

	if (Character == nullptr)
	{
		return;
	}

	Character->TriggerJumpSectionCombo();
}

void UTriggerJumpSectionNS::DoNotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::DoNotifyEnd(MeshComp, Animation);
}
