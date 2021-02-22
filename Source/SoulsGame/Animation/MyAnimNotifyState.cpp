// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotifyState.h"

void UMyAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	UE_LOG(LogTemp, Warning, TEXT("Notify begin"));
	if (!HasTriggered)
	{
		//HasTriggered = true;
		this->DoNotifyBegin(MeshComp, Animation, TotalDuration);
	}
}

void UMyAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	/*
	UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
	if (!AnimInstance)
	{
		return;
	}
	

	FAnimMontageInstance* RootMotion = AnimInstance->GetActiveMontageInstance();
	if (!RootMotion)
	{
		return;
	}

	if (RootMotion->IsPlaying() != false)
	{
		HasTriggered = false;
	}
	

	UE_LOG(LogTemp, Warning, TEXT("Notify end"));
	*/
}

void UMyAnimNotifyState::DoNotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                       float TotalDuration)
{

	// Override me!

}
