// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Abilities/GameplayAbility.h"
#include "MyGameplayEffect.h"

#include "MyGameplayAbility.generated.h"

// Helper to organize gameplay abilities
USTRUCT()
struct FGameplayAbilityDataContainer
{
	GENERATED_BODY()
	
	FGameplayAbilitySpec GameplayAbilitySpec;
	FGameplayAbilitySpecHandle GameplayAbilitySpecHandle;
	
	// ReSharper disable once CppUE4ProbableMemoryIssuesWithUObject
	// Always check for null before using this
	UGameplayAbility * MyGameplayAbility; // Useful only if this data container is only one

	bool IsMany = true;
	
	// Only useful if more than one (not sure how common this is yet)
	TArray<UGameplayAbility*> GetAllGameplayAbilityInstances() const;

	void SetGameplayAbility(UGameplayAbility * Ability);

	bool GetIsMany() const;

	FString GetMyGameplayAbilityName() const;

	bool HasTag(const FName TagName) const;

	// Note: Would it be useful to also store the UMyAbilityAsset?
};

/**
 * 
 */
UCLASS()
class SOULSGAME_API UMyGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UMyGameplayEffect>> AppliedGameplayEffects;

	FGameplayEffectDataContainer GameplayEffectsContainer;
	
	// Wrapper around K2, because it's protected.
	TArray<FActiveGameplayEffectHandle> ApplyGameplayEffectSpecToTarget(const FGameplayEffectSpecHandle EffectSpecHandle, FGameplayAbilityTargetDataHandle TargetData);

	FGameplayEffectData & InitializeGameplayEffectData(FGameplayEffectDataContainer& EffectsContainer, TSubclassOf<UMyGameplayEffect> & Effect) const;
	
protected:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	void InitializeEffectContainerHelper();

};
