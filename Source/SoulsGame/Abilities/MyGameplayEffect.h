// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Abilities/GameplayAbilityTargetTypes.h"

#include "MyGameplayEffect.generated.h"

class UMyGameplayEffect;
// Helper to organize gameplay abilities
USTRUCT()
struct FGameplayEffectDataContainer
{
	GENERATED_BODY()
	
	FGameplayEffectSpec GameplayEffectSpec;
	FGameplayEffectSpecHandle GameplayEffectSpecHandle;
	
	TArray<FActiveGameplayEffectHandle> ActiveGameplayEffectHandles;
	
	// ReSharper disable once CppUE4ProbableMemoryIssuesWithUObject
	// Always check for null before using this
	UMyGameplayEffect * MyGameplayEffect; // Useful only if this data container is only one
	FGameplayAbilityTargetDataHandle TargetData;
	// Note: Would it be useful to also store the UMyAbilityAsset?
};


/**
 * 
 */
UCLASS()
class SOULSGAME_API UMyGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()
	
};
