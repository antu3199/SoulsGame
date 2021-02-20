// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeStopAbilityActor.h"

ATimeStopAbilityActor::ATimeStopAbilityActor()
{
	PrimaryActorTick.bCanEverTick = true;

}



void ATimeStopAbilityActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// TODO: Change size

	TArray<AActor *> OverlappingActors;
	this->GetOverlappingActors(OverlappingActors);

	this->Ability->ApplyEffectsToActors(OverlappingActors);


	
	
}
