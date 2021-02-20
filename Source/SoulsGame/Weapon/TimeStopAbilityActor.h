// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityActor.h"
#include "TimeStopAbilityActor.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API ATimeStopAbilityActor : public AAbilityActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeStopAbilityActor();


	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	UPROPERTY()
	TArray<AActor *> HitActors;

	bool IsOverlapping;

	UFUNCTION()
	void OnTagAdded(const FGameplayTag CooldownTag, int32 NewCount);

	UFUNCTION()
	void OnTagRemoved(const FGameplayTag CooldownTag, int32 NewCount);
};
