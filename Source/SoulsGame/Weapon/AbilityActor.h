// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SoulsGame/Abilities/MyGameplayAbility.h"

#include "AbilityActor.generated.h"

UCLASS()
class SOULSGAME_API AAbilityActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbilityActor();
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	virtual void Initialize(UMyGameplayAbility * DataContainer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* Base;

	
	UPROPERTY()
	UMyGameplayAbility * Ability;
	
};
