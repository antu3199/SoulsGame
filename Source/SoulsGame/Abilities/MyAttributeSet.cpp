// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeSet.h"


#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "SoulsGame/CharacterBase.h"


UMyAttributeSet::UMyAttributeSet()
    : Health(100.f), MaxHealth(100.f), AttackPower(1.0f), Damage(0.0f)
{
    
}


void UMyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    if (Attribute == GetMaxHealthAttribute())
    {
        this->KeepSamePercentageAfterMaxChange(this->Health, this->MaxHealth, NewValue, GetHealthAttribute());
    }
}

void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
    UAbilitySystemComponent * Source = Context.GetOriginalInstigatorAbilitySystemComponent();
    const FGameplayTagContainer & SourceTags =  *(Data.EffectSpec.CapturedSourceTags.GetAggregatedTags());

    AActor * TargetActor = nullptr;
    AController * TargetController = nullptr;
    ACharacterBase * TargetCharacter = nullptr;
    this->GetAbilitySystemActorProperties(&Data.Target, TargetActor, TargetController, TargetCharacter);

    AActor* SourceActor = nullptr;
    AController* SourceController = nullptr;
    ACharacterBase* SourceCharacter = nullptr;

    this->GetAbilitySystemActorProperties(Source, SourceActor, SourceController, SourceCharacter);
    
    
    float DeltaValue = 0;
    if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
    {
        DeltaValue = Data.EvaluatedData.Magnitude;
    }

    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
        if (TargetCharacter)
        {
            TargetCharacter->HandleHealthChanged(DeltaValue, SourceTags);
        }
    }
    else if (Data.EvaluatedData.Attribute == GetDamageAttribute())
    {
        if (Context.GetEffectCauser())
        {
            SourceActor = Context.GetEffectCauser();
        }

        // Do a hit result
        FHitResult HitResult;
        if (Context.GetHitResult())
        {
            HitResult = *Context.GetHitResult();
        }

        const float LocalDamageDone = GetDamage();
        SetDamage(0.0f);

        if (LocalDamageDone > 0)
        {
            const float OldHealth = GetHealth();
            const float NewHealth = FMath::Clamp(OldHealth - LocalDamageDone, 0.0f, GetMaxHealth());
            SetHealth(NewHealth);

            UE_LOG(LogTemp, Warning, TEXT("OldHealth: %f , NewHealth %f"), OldHealth, NewHealth);
            if (TargetCharacter)
            {
                TargetCharacter->HandleDamage(LocalDamageDone, HitResult, SourceTags, SourceCharacter, SourceActor);
                TargetCharacter->HandleHealthChanged(-LocalDamageDone, SourceTags);
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Unknown attribute!"));
    }

}



// Replicated props ================================================

void UMyAttributeSet::GetLifetimeReplicatedProps(::TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UMyAttributeSet, Health);
    DOREPLIFETIME(UMyAttributeSet, MaxHealth);
    DOREPLIFETIME(UMyAttributeSet, AttackPower);
    DOREPLIFETIME(UMyAttributeSet, Health);
    
}

void UMyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Health, OldHealth);
}

void UMyAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MaxHealth, OldMaxHealth);
}

void UMyAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, AttackPower, OldAttackPower);
}



// Helper functions =======================================================

void UMyAttributeSet::KeepSamePercentageAfterMaxChange(const FGameplayAttributeData& AffectedAttribute,
    const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty) const
{
    UAbilitySystemComponent * AbilityComp = GetOwningAbilitySystemComponent();
    const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
    if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
    {
        const float CurrentValue = AffectedAttribute.GetCurrentValue();
        const float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentMaxValue : NewMaxValue;
        AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
    }
}

void UMyAttributeSet::GetAbilitySystemActorProperties(UAbilitySystemComponent* Component, AActor*& ReturnActor,
    AController*& ReturnController, ACharacterBase*& ReturnCharacter) const
{
    if (Component->AbilityActorInfo.IsValid() && Component->AbilityActorInfo->AvatarActor.IsValid())
    {
        ReturnActor = Component->AbilityActorInfo->AvatarActor.Get();
        ReturnController = Component->AbilityActorInfo->PlayerController.Get();
        if (ReturnController)
        {
            ReturnCharacter = Cast<ACharacterBase>(ReturnController->GetPawn());
        }
        else
        {
            ReturnCharacter = Cast<ACharacterBase>(ReturnActor);
        }
    }
}
