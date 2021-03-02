// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsStunned.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API UBTService_IsStunned : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_IsStunned();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
