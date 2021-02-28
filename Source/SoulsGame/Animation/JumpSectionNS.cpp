// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpSectionNS.h"


void UJumpSectionNS::DoNotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::DoNotifyBegin(MeshComp, Animation, TotalDuration);

	ACharacterBase * Character = GetCharacter(MeshComp);
	Character->SetComboJumpSection(this);
}

void UJumpSectionNS::DoNotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::DoNotifyEnd(MeshComp, Animation);
	
	ACharacterBase * Character = GetCharacter(MeshComp);
	Character->SetComboJumpSection(nullptr);
}
