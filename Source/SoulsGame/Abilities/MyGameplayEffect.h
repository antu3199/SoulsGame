// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "GameplayEffect.h"
#include "Abilities/GameplayAbilityTypes.h"


#include "MyGameplayEffect.generated.h"

class UMyGameplayEffect;
class ACharacterBase; 
class UMyGameplayAbility;

// Helper to organize gameplay abilities
USTRUCT()
struct FGameplayEffectData
{
	GENERATED_BODY()

	FGameplayEffectSpec GameplayEffectSpec;
	FGameplayEffectSpecHandle GameplayEffectSpecHandle;
	
	TArray<FActiveGameplayEffectHandle> ActiveGameplayEffectHandles;
	
	// ReSharper disable once CppUE4ProbableMemoryIssuesWithUObject
	// Always check for null before using this
	UMyGameplayEffect * GameplayEffect; // Useful only if this data container is only one
	FGameplayAbilityTargetDataHandle TargetData;

	void AddTargets(const TArray<FHitResult>& HitResults, const TArray<AActor*> & TargetActors);
	// Note: Would it be useful to also store the UMyAbilityAsset?
};

USTRUCT()
struct FGameplayEffectDataContainer
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TArray<FGameplayEffectData> ActiveGameplayEffects;

	bool DoesEffectContainerHaveEffects() const;
};


/**
 * 
 */
UCLASS()
class SOULSGAME_API UMyGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()

public:
	static void GetTargets_UseEventData(ACharacterBase* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors);
	
};
