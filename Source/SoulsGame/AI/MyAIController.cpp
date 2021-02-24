// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"


void AMyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
	}
}

void AMyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
