// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpSectionNS.h"


void UJumpSectionNS::DoNotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::DoNotifyBegin(MeshComp, Animation, TotalDuration);

	UE_LOG(LogTemp, Display, TEXT("UJumpSectionNS Begin"));

	ACharacterBase * Character = GetCharacter(MeshComp);
	if (Character == nullptr)
	{
		return;
	}
	
	Character->SetComboJumpSection(this);
	Character->JumpSectionCancellable = false;
	Character->BufferedInput.Reset();
	Character->BufferedInput.StartBufferingInput = true;
	UE_LOG(LogTemp, Display, TEXT("TriggerJumpSectionStart!"));

	

}

void UJumpSectionNS::DoNotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::DoNotifyEnd(MeshComp, Animation);



	UE_LOG(LogTemp, Display, TEXT("UJumpSectionNS End"));
	
	ACharacterBase * Character = GetCharacter(MeshComp);
	if (Character == nullptr || Character->JumpSectionCancellable)
	{
		return;
	}
	
	Character->JumpSectionCancellable = true;
	Character->CheckBufferedInput();
	Character->BufferedInput.StartBufferingInput = false;
	Character->SetComboJumpSection(nullptr);
	
}
