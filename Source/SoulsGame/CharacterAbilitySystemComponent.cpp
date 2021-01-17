// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAbilitySystemComponent.h"

#include "GameplayTagsManager.h"
#include "MyGameplayAbility.h"


// Gets activatableAbilities with tags
void UCharacterAbilitySystemComponent::GetActiveAbilitiesWithTags(const FGameplayTagContainer & GameplayTagContainer, OUT TArray<UMyGameplayAbility *> ActiveAbilities) const
{
    // Get all abilities matching the gameplay tag container
    TArray<FGameplayAbilitySpec *> AbilitiesToActivate;
    GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, AbilitiesToActivate, true);

    for (FGameplayAbilitySpec * Spec : AbilitiesToActivate)
    {
        // Iterate all instances on this ability spec
        // Note that there can be two abilities with the same name
        // e.g. two abilities named "melee", with one requiring unarmed and one requiring weapon.
        TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();

        for (UGameplayAbility * ActiveAbility : AbilityInstances)
        {
            ActiveAbilities.Add(Cast<UMyGameplayAbility>(ActiveAbility));
        }
    }
}

void UCharacterAbilitySystemComponent::GetActiveAbilitiesWithTag(const FName TagName,
    OUT const TArray<UMyGameplayAbility*> ActiveAbilities) const
{
    FGameplayTagContainer TagContainer;
    const FGameplayTag Tag = UGameplayTagsManager::Get().RequestGameplayTag(TagName, true);
    TagContainer.AddTag(Tag);

    this->GetActiveAbilitiesWithTags(TagContainer, ActiveAbilities);
}

bool  UCharacterAbilitySystemComponent::IsUsingAbilityWithTag(const FName Tag) const
{
    // ReSharper disable once IdentifierTypo
    const TArray<UMyGameplayAbility*> MyAbilities;
    this->GetActiveAbilitiesWithTag(Tag, MyAbilities);
    return MyAbilities.Num() > 0;
}