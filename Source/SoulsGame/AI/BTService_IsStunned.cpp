// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsStunned.h"


#include "AIController.h"
#include "GameplayTagsManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SoulsGame/CharacterBase.h"

UBTService_IsStunned::UBTService_IsStunned()
{
	NodeName = "Set is stunned";
}

void UBTService_IsStunned::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return;
	}

	ACharacterBase * Character = Cast<ACharacterBase>(OwnerComp.GetAIOwner()->GetPawn());

	const FGameplayTag StunTag = UGameplayTagsManager::Get().RequestGameplayTag(TEXT("State.Stun"));
	
	const bool IsStunned = Character->GetAbilitySystemComponent()->HasMatchingGameplayTag(StunTag);
	UE_LOG(LogTemp, Warning, TEXT("Is stunned? %d"), IsStunned);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), IsStunned);

}
