// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpSectionNS.h"


void UJumpSectionNS::DoNotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::DoNotifyBegin(MeshComp, Animation, TotalDuration);

	ACharacterBase * Character = GetCharacter(MeshComp);
	if (Character == nullptr)
	{
		return;
	}
	
	Character->SetComboJumpSection(this);
	Character->JumpSectionCancellable = false;
	UE_LOG(LogTemp, Display, TEXT("TriggerJumpSectionStart!"));

}

void UJumpSectionNS::DoNotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::DoNotifyEnd(MeshComp, Animation);
	
	ACharacterBase * Character = GetCharacter(MeshComp);
	if (Character == nullptr || Character->JumpSectionCancellable)
	{
		
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("TriggerJumpSectionEnd!"));

	if (Character->TriggerJumpSectionCombo())
	{
		UE_LOG(LogTemp, Display, TEXT("TriggerJumpSection success!"));
	}
	else
	{
		Character->JumpSectionCancellable = true;
		UE_LOG(LogTemp, Display, TEXT("TriggerJumpSection failed!"));
	}
	
	
	Character->SetComboJumpSection(nullptr);


	
}
