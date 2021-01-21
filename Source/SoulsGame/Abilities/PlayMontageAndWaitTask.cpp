// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayMontageAndWaitTask.h"


#include "AbilitySystemGlobals.h"
#include "GameFramework/Character.h"
#include "SoulsGame/CharacterAbilitySystemComponent.h"

UPlayMontageAndWaitTask::UPlayMontageAndWaitTask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    this->TaskData.Rate = 1.f;
    this->TaskData.StopWhenAbilityEnds = true;
}

void UPlayMontageAndWaitTask::Activate()
{
    Super::Activate();
    UE_LOG(LogTemp, Warning, TEXT("UPlayMontageAndWaitTask Activate"));

    if (UAbilityTask::Ability != nullptr && UAbilityTask::Ability != this->TaskData.OwningAbility)
    {
        UE_LOG(LogTemp, Warning, TEXT("Warning: Task ability not the same as owning ability!"));
        return;
    }
    UCharacterAbilitySystemComponent* MyAbilitySystemComponent = this->GetTargetAbilitySystemComponent();
    
    if (!MyAbilitySystemComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("Error: Could not find ability system!"));
        return;
    }

    const FGameplayAbilityActorInfo *ActorInfo = Ability->GetCurrentActorInfo();
    UAnimInstance * AnimInstance = ActorInfo->GetAnimInstance();
    if (AnimInstance == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Error: Could not find anim instance!"));
        return;
    }

    if (!ShouldBroadcastAbilityTaskDelegates())
    {
        return;
    }

    const auto OnGameplayEventCallback = FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UPlayMontageAndWaitTask::OnGameplayEvent);

    const float CanPlayMontage = MyAbilitySystemComponent->PlayMontage(Ability, Ability->GetCurrentActivationInfo(), TaskData.MontageToPlay, TaskData.Rate, TaskData.StartSection);
    if (!CanPlayMontage)
    {
        UE_LOG(LogTemp, Error, TEXT("Error: Failed to play Montage!"));
        return;
    }

    EventDelegateHandle = AbilitySystemComponent->AddGameplayEventTagContainerDelegate(this->TaskData.EventTags, OnGameplayEventCallback);
    CancelledDelegateHandle = Ability->OnGameplayAbilityCancelled.AddUObject(this, &UPlayMontageAndWaitTask::OnAbilityCancelled);

    this->BlendingOutDelegate.BindUObject(this, &UPlayMontageAndWaitTask::OnMontageBlendingOut);
    AnimInstance->Montage_SetBlendingOutDelegate(this->BlendingOutDelegate, TaskData.MontageToPlay);

    this->MontageEndedDelegate.BindUObject(this, &UPlayMontageAndWaitTask::OnMontageEnded);
    AnimInstance->Montage_SetEndDelegate(this->BlendingOutDelegate, TaskData.MontageToPlay);

    // Set Anim translation scale
    ACharacter* Character = Cast<ACharacter>(GetAvatarActor());
    if (Character && (Character->GetLocalRole() == ROLE_Authority ||
        (Character->GetLocalRole() == ROLE_AutonomousProxy && Ability->GetNetExecutionPolicy() == EGameplayAbilityNetExecutionPolicy::LocalPredicted)))
    {
        Character->SetAnimRootMotionTranslationScale(TaskData.AnimRootMotionTranslationScale);
    }

    this->PlayedMontage = true;

    if (!this->PlayedMontage && ShouldBroadcastAbilityTaskDelegates())
    {
        OnCancelled.Broadcast(FGameplayTag(), FGameplayEventData());
    }
}

void UPlayMontageAndWaitTask::ExternalCancel()
{
    Super::ExternalCancel();
}

void UPlayMontageAndWaitTask::OnDestroy(bool AbilityEnded)
{

    if (Ability)
    {
        Ability->OnGameplayAbilityCancelled.Remove(CancelledDelegateHandle);
        if (AbilityEnded && TaskData.StopWhenAbilityEnds)
        {
            // TODO: StopPlayingMontage();
        }
    }

    UCharacterAbilitySystemComponent * MyAbilitySystemComponent = this->GetTargetAbilitySystemComponent();
    if (MyAbilitySystemComponent)
    {
        MyAbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(TaskData.EventTags, EventDelegateHandle);
    }

    Super::OnDestroy(AbilityEnded);
}

void UPlayMontageAndWaitTask::OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload)
{
    if (this->AbilitySystemComponent != nullptr)
    {
        this->OnAbilityCancelled();
        Super::ExternalCancel();
    }
}

UCharacterAbilitySystemComponent* UPlayMontageAndWaitTask::GetTargetAbilitySystemComponent() const
{
    return Cast<UCharacterAbilitySystemComponent>(this->AbilitySystemComponent);
}

void UPlayMontageAndWaitTask::OnAbilityCancelled()
{
    //if (StopPlayingMontage()) // TODO:
    OnCancelled.Broadcast(FGameplayTag(), FGameplayEventData());
}

void UPlayMontageAndWaitTask::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
}

void UPlayMontageAndWaitTask::OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted)
{
}

UPlayMontageAndWaitTask * UPlayMontageAndWaitTask::CreatePlayMontageAndWaitEvent(FPlayMontageAndWaitTaskData& TaskData)
{
    UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Rate(TaskData.Rate);
    
    UPlayMontageAndWaitTask * MyObj = NewAbilityTask<UPlayMontageAndWaitTask>(TaskData.OwningAbility, TaskData.TaskInstanceName);
    MyObj->TaskData = TaskData; // Copy data by value for ownership
    
    return MyObj;
}
