// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsDead.h"

#include "AIController.h"
#include "GameplayTagsManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SoulsGame/CharacterBase.h"

UBTService_IsDead::UBTService_IsDead()
{
	NodeName = "Set is dead";
}

void UBTService_IsDead::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return;
	}

	ACharacterBase * Character = Cast<ACharacterBase>(OwnerComp.GetAIOwner()->GetPawn());

	
	const bool IsDead = Character->GetIsDead();
	// UE_LOG(LogTemp, Warning, TEXT("Is stunned? %d"), IsStunned);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), IsDead);
}
