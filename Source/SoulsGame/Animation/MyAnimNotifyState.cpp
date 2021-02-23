// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotifyState.h"


#include "GameplayTagsManager.h"
#include "SoulsGame/CharacterBase.h"

UMyAnimNotifyState::UMyAnimNotifyState()
{
	this->HasTriggered = false;
	this->CachedTime = 0;
}

void UMyAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	
	if (this->ShouldDoNotify(MeshComp))
	{
		this->DoNotifyBegin(MeshComp, Animation, TotalDuration);
	}
	
	//}
}


void UMyAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
	if (!AnimInstance)
	{
		HasTriggered = false;
		return;
	}
	

	FAnimMontageInstance* RootMotion = AnimInstance->GetActiveMontageInstance();
	if (!RootMotion)
	{
		HasTriggered = false;
		return;
	}

	if (RootMotion->bPlaying == false)
	{
		this->CachedTime = RootMotion->GetPosition();
		this->HasTriggered = true;

	}

}


void UMyAnimNotifyState::DoNotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                       float TotalDuration)
{

	// Override me!

}

bool UMyAnimNotifyState::ShouldDoNotify(USkeletalMeshComponent* MeshComp)
{
	UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
	if (!AnimInstance)
	{
		return true;
	}

	FAnimMontageInstance* RootMotion = AnimInstance->GetActiveMontageInstance();
	if (!RootMotion)
	{
		return true;
	}

	const float Abs = FMath::Abs(RootMotion->GetPosition() - this->CachedTime);

	if (Abs > this->MultiNotifyThresh)
	{
		this->HasTriggered = false;
	}

	return !this->HasTriggered;

}
