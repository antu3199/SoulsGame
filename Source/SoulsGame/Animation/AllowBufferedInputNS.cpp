// Fill out your copyright notice in the Description page of Project Settings.


#include "AllowBufferedInputNS.h"

void UAllowBufferedInputNS::DoNotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::DoNotifyBegin(MeshComp, Animation, TotalDuration);

	ACharacterBase * Character = GetCharacter(MeshComp);

	if (Character == nullptr)
	{
		return;
	}

	Character->BufferedInput.StartBufferingInput = true;

}

void UAllowBufferedInputNS::DoNotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::DoNotifyEnd(MeshComp, Animation);

	ACharacterBase * Character = GetCharacter(MeshComp);

	if (Character == nullptr)
	{
		return;
	}

	Character->CheckBufferedInput();
	Character->BufferedInput.StartBufferingInput = false;

}
