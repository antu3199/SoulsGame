// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AbilitySystemComponent.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncTaskEffectStackChanged.generated.h"


USTRUCT(BlueprintType)
struct FAsyncTaskEffectStackChangedData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UAbilitySystemComponent * AbilitySystemComponent;

	UPROPERTY(EditAnywhere)
	FGameplayTag EffectGameplayTag;

	bool DestroyOnZero = true;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGameplayEffectStackChanged, FGameplayTag, EffectGameplayTag, FActiveGameplayEffectHandle, Handle, int32, NewStackCount, int32, OldStackCount);

/**
 * 
 */
UCLASS()
class SOULSGAME_API UAsyncTaskEffectStackChanged : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	static UAsyncTaskEffectStackChanged * CreateGameplayEffectStackChanged(FAsyncTaskEffectStackChangedData & TaskData);

	void EndTask();

	UPROPERTY(BlueprintAssignable)
	FOnGameplayEffectStackChanged OnGameplayEffectStackChange;

protected:
	FAsyncTaskEffectStackChangedData TaskData;


	virtual void OnActiveGameplayEffectAddedCallback(UAbilitySystemComponent * Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);
	virtual void OnRemoveGameplayEffectCallback(const FActiveGameplayEffect& EffectRemoved);

	virtual void GameplayEffectStackChanged(FActiveGameplayEffectHandle EffectHandle, int32 NewStackCount, int32 PreviousStackCount);
};
