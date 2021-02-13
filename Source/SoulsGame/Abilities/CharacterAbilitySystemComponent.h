// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MyGameplayAbility.h"

#include "CharacterAbilitySystemComponent.generated.h"

#define OUT





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
	bool ActivateAbilityWithTag(const FName TagName);

    FGameplayAbilityDataContainer & AddNewGameplayAbilityDataContainer()
    {
	    this->GameplayAbilityDataContainer.Add(FGameplayAbilityDataContainer());
    	return this->GameplayAbilityDataContainer.Last();
    }

	const TArray<FGameplayAbilityDataContainer> & GetGameplayAbilityDataContainer() const
	{
	    return this->GameplayAbilityDataContainer;
    }

protected:
	TArray<FGameplayAbilityDataContainer> GameplayAbilityDataContainer;
	
};
