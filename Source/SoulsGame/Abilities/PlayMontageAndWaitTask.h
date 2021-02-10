// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "SoulsGame/Abilities/CharacterAbilitySystemComponent.h"

#include "PlayMontageAndWaitTask.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayMontageAndWaitTaskDelegate, FGameplayTag, varNameFGameplayTag, FGameplayEventData, varNameFGameplayEventData);

USTRUCT(BlueprintType)
struct FPlayMontageAndWaitTaskData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName TaskInstanceName = "TaskName";
	UPROPERTY(EditAnywhere)
	UAnimMontage *MontageToPlay;
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer EventTags;
	UPROPERTY(EditAnywhere)
	float Rate = 1.0;
	UPROPERTY(EditAnywhere)
	FName StartSection = "None";
	UPROPERTY(EditAnywhere)
	bool StopWhenAbilityEnds = true;
	UPROPERTY(EditAnywhere)
	float AnimRootMotionTranslationScale = 1.0;
	UPROPERTY()
	UGameplayAbility* OwningAbility = nullptr;
};

/**
 * 
 */
UCLASS()
class SOULSGAME_API UPlayMontageAndWaitTask : public UAbilityTask
{
	GENERATED_BODY()


public:
	UPlayMontageAndWaitTask(const FObjectInitializer & ObjectInitializer);

	// Callbacks
	FPlayMontageAndWaitTaskDelegate OnCompleted;
	FPlayMontageAndWaitTaskDelegate OnBlendOut;
	FPlayMontageAndWaitTaskDelegate OnInterrupted;
	FPlayMontageAndWaitTaskDelegate OnCancelled;

	// Triggering gameplay event
	FPlayMontageAndWaitTaskDelegate OnEventReceived;

	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility"))
	static UPlayMontageAndWaitTask *CreatePlayMontageAndWaitEvent(FPlayMontageAndWaitTaskData & TaskData);

	
protected:
	virtual void Activate() override;
	virtual void ExternalCancel() override;
	virtual void OnDestroy(bool AbilityEnded) override;


	FPlayMontageAndWaitTaskData TaskData;
	UCharacterAbilitySystemComponent * GetTargetAbilitySystemComponent() const;

	// Delegate handles
	FDelegateHandle EventDelegateHandle;
	FDelegateHandle CancelledDelegateHandle;
	FOnMontageBlendingOutStarted BlendingOutDelegate;
	FOnMontageEnded MontageEndedDelegate;

	// Delegate callbacks
	void OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload);
	bool StopPlayingMontage();
	void OnAbilityCancelled();
	void OnMontageEnded(UAnimMontage  * Montage, bool bInterrupted);
	void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);

	bool PlayedMontage = false;
};
