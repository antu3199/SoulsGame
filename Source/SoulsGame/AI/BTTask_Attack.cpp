// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"


#include "AIController.h"
#include "SoulsGame/CharacterBase.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = "Attack";
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ACharacterBase * Character = Cast<ACharacterBase>(OwnerComp.GetAIOwner()->GetPawn());

	Character->UseAbility("Ability.Melee");
	
	return EBTNodeResult::Succeeded;
	
}
