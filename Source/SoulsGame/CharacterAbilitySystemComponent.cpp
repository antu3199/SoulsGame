// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAbilitySystemComponent.h"

#include "GameplayTagsManager.h"
#include "MyGameplayAbility.h"

// FGameplayAbilityDataContainer =====================================================

// Only useful if more than one (not sure how common this is yet)
TArray<UGameplayAbility*> FGameplayAbilityDataContainer::GetAllGameplayAbilityInstances() const
{
    if (IsMany)
    {
        return GameplayAbilitySpec.GetAbilityInstances();
    }
    else
    {
        if (MyGameplayAbility != nullptr)
        {
            return TArray<UGameplayAbility*>{MyGameplayAbility};
        }
        else
        {
            return TArray<UGameplayAbility*>();
        }
    }
}

void FGameplayAbilityDataContainer::SetGameplayAbility(UGameplayAbility * Ability)
{
    this->MyGameplayAbility = Ability;
    this->IsMany = false;
}


bool FGameplayAbilityDataContainer::GetIsMany() const
{
    return IsMany;
}

FString FGameplayAbilityDataContainer::GetMyGameplayAbilityName() const
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

bool FGameplayAbilityDataContainer::HasTag(const FName TagName) const
{
    const FGameplayTag Tag = UGameplayTagsManager::Get().RequestGameplayTag(TagName);
    
    const TArray<UGameplayAbility*> MyGameplayAbilities = this->GetAllGameplayAbilityInstances();
    if (MyGameplayAbilities.Num() == 0)
    {
        return false;
    }
    else
    {
        for (UGameplayAbility* const& Ability : MyGameplayAbilities)
        {
            if (Ability->AbilityTags.HasTag(Tag))
            {
                return true;
            }
        }

        return false;
    }
}

// UCharacterAbilitySystemComponent =====================================

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

bool UCharacterAbilitySystemComponent::ActivateAbilityWithTag(const FName TagName)
{
    const TArray<FGameplayAbilityDataContainer> & ContainerArray = this->GetGameplayAbilityDataContainer();
	
    for (int i = 0; i < ContainerArray.Num(); i++)
    {
        const FGameplayAbilityDataContainer & Container = ContainerArray[i];

        if (Container.HasTag(TagName))
        {
            return this->TryActivateAbility(Container.GameplayAbilitySpecHandle);
        }
    }

    return false;
}
