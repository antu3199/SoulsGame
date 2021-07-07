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


	if (Character->BufferedJumpSectionCombo)
	{
		UE_LOG(LogTemp, Display, TEXT("TriggerJumpSectionCombo!"));
		Character->TriggerJumpSectionCombo();
	}
	else
	{
		Character->JumpSectionCancellable = true;
		UE_LOG(LogTemp, Display, TEXT("TriggerJumpSection failed!"));
	}
/*
	if ()
	{
		UE_LOG(LogTemp, Display, TEXT("TriggerJumpSection success!"));
	}
	else
	{

	}*/
	
	
	Character->SetComboJumpSection(nullptr);


	
}
