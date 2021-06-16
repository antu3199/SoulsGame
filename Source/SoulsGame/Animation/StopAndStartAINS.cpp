// Fill out your copyright notice in the Description page of Project Settings.


#include "StopAndStartAINS.h"


#include "BrainComponent.h"
#include "SoulsGame/AI/MyAIController.h"

void UStopAndStartAINS::DoNotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                      float TotalDuration)
{
	Super::DoNotifyBegin(MeshComp, Animation, TotalDuration);

	if (!MeshComp || !MeshComp->GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("UStopAndStartAINS:: Mesh Comp null"))
		return;
	}

	ACharacterBase * CharacterBase = Cast<ACharacterBase>(MeshComp->GetOwner());
	if (!CharacterBase)
	{
		UE_LOG(LogTemp, Warning, TEXT("UStopAndStartAINS::DoNotifyBegin Character null"))
		return;
	}

	AController* Controller = CharacterBase->GetController();
	if (!Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("UStopAndStartAINS::DoNotifyBegin Controller null"))
		return;
	}

	AMyAIController * AIController = Cast<AMyAIController>(Controller);
	if (!AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("UStopAndStartAINS::DoNotifyBegin AICharacter null"))
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("UStopAndStartAINS::DoNotifyBegin Stop movement"));

	AIController->StopMovement();
	AIController->BrainComponent->StopLogic("Stop by attacked");
}

void UStopAndStartAINS::DoNotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::DoNotifyEnd(MeshComp, Animation);

	if (!MeshComp || !MeshComp->GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("UStopAndStartAINS::DoNotifyEnd Mesh Comp null"))
		return;
	}

	ACharacterBase * CharacterBase = Cast<ACharacterBase>(MeshComp->GetOwner());
	if (!CharacterBase)
	{
		UE_LOG(LogTemp, Warning, TEXT("UStopAndStartAINS::DoNotifyEnd Character null"))
		return;
	}

	AController* Controller = CharacterBase->GetController();
	if (!Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("UStopAndStartAINS::DoNotifyEnd Controller null"))
		return;
	}

	AMyAIController * AIController = Cast<AMyAIController>(Controller);
	if (!AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("UStopAndStartAINS::DoNotifyEnd AICharacter null"))
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("UStopAndStartAINS::DoNotifyEnd RestartLogic"));

	AIController->BrainComponent->RestartLogic();
}
