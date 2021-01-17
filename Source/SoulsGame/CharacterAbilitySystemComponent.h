// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MyGameplayAbility.h"

#include "CharacterAbilitySystemComponent.generated.h"

#define OUT


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
	TArray<UGameplayAbility*> GetAllGameplayAbilityInstances() const
	{
		return GameplayAbilitySpec.GetAbilityInstances();
	}

	void SetGameplayAbility(UGameplayAbility * Ability)
	{
		this->MyGameplayAbility = Ability;
		this->IsMany = false;
	}

	bool GetIsMany() const
	{
		return IsMany;
	}

	FString GetMyGameplayAbilityName() const
	{
		if (MyGameplayAbility == nullptr || this->GetIsMany())
		{
			return TEXT("");
		}
		else
		{
			return MyGameplayAbility->AbilityTags.ToString();
		}
	}

	// Note: Would it be useful to also store the UMyAbilityAsset?
};


/**
 * 
 */
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOULSGAME_API UCharacterAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void GetActiveAbilitiesWithTags(const ::FGameplayTagContainer& GameplayTagContainer, OUT TArray<UMyGameplayAbility*> ActiveAbilities) const;
	void GetActiveAbilitiesWithTag(const FName TagName, OUT TArray<UMyGameplayAbility*> ActiveAbilities) const;
	bool  IsUsingAbilityWithTag(const FName Tag) const;

	TArray<FGameplayAbilityDataContainer> GameplayAbilityDataContainer;

    FGameplayAbilityDataContainer & AddNewGameplayAbilityDataContainer()
    {
	    this->GameplayAbilityDataContainer.Add(FGameplayAbilityDataContainer());
    	return this->GameplayAbilityDataContainer.Last();
    }
	
};
