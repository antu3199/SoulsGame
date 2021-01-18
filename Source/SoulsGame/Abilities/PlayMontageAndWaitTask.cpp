// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayMontageAndWaitTask.h"

#include "SoulsGame/CharacterAbilitySystemComponent.h"

UPlayMontageAndWaitTask::UPlayMontageAndWaitTask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    
}

void UPlayMontageAndWaitTask::Activate()
{
    Super::Activate();
    UE_LOG(LogTemp, Warning, TEXT("UPlayMontageAndWaitTask Activate"));

    UCharacterAbilitySystemComponent* MyAbilitySystemComponent = this->GetTargetAbilitySystemComponent();
    //MyAbilitySystemComponent->AddGameplayEventTagContainerDelegate();
    
}

void UPlayMontageAndWaitTask::ExternalCancel()
{
    Super::ExternalCancel();
}

void UPlayMontageAndWaitTask::OnDestroy(bool AbilityEnded)
{
    Super::OnDestroy(AbilityEnded);
}

UCharacterAbilitySystemComponent* UPlayMontageAndWaitTask::GetTargetAbilitySystemComponent() const
{
    return Cast<UCharacterAbilitySystemComponent>(this->AbilitySystemComponent);
}
