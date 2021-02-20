// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityActor.h"

#include <xutility>

// Sets default values
AAbilityActor::AAbilityActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Base = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Base->SetHiddenInGame(true);
	SetRootComponent(Base);
}

void AAbilityActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}

void AAbilityActor::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
}

void AAbilityActor::Initialize(UMyGameplayAbility* DataContainer)
{
	this->Ability = DataContainer;
}

