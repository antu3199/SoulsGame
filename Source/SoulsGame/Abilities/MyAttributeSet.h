// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "MyAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
class ACharacterBase;

UCLASS()
class SOULSGAME_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
    UMyAttributeSet();

    
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    virtual void GetLifetimeReplicatedProps(::TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UMyAttributeSet, Health)

    UPROPERTY(BlueprintReadOnly, Category = "MaxHealth", ReplicatedUsing = OnRep_MaxHealth)
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxHealth)

    UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_AttackPower)
    FGameplayAttributeData AttackPower;
    ATTRIBUTE_ACCESSORS(UMyAttributeSet, AttackPower)

    // Damage is a 'temporary' attribute used by the DamageExecution to calculate final damage, which then turns into -Health 
    // Temporary value that only exists on the Server. Not replicated.
    UPROPERTY(BlueprintReadOnly, Category = "Damage", meta = (HideFromLevelInfos))
    FGameplayAttributeData Damage;
    ATTRIBUTE_ACCESSORS(UMyAttributeSet, Damage)
    
protected:

    UFUNCTION()
    virtual void OnRep_Health(const FGameplayAttributeData & OldHealth);

    UFUNCTION()
    virtual void OnRep_MaxHealth(const FGameplayAttributeData & OldMaxHealth);
    
    UFUNCTION()
    virtual void OnRep_AttackPower(const FGameplayAttributeData & OldAttackPower);
    
    // Helper function to keep same percentage after applying change to max value of an attribute

    void KeepSamePercentageAfterMaxChange(const FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty) const;

    void GetAbilitySystemActorProperties(UAbilitySystemComponent * Component, AActor *& ReturnActor, AController *& ReturnController, ACharacterBase *& ReturnCharacter) const;
};
