// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AbilitySystemComponent.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncTaskTagChanged.generated.h"

USTRUCT(BlueprintType)
struct FAsyncTaskTagChangedData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UAbilitySystemComponent * AbilitySystemComponent;

	UPROPERTY(EditAnywhere)
	FGameplayTag EffectGameplayTag;

	bool DestroyOnZero = true;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTagChanged, FGameplayTag, Tag,  int32, NewCount );


/**
 * 
 */
UCLASS()
class SOULSGAME_API UAsyncTaskTagChanged : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable)
	static UAsyncTaskTagChanged * CreateTagChangedTask(FAsyncTaskTagChangedData & TaskData);

	void EndTask();

	UPROPERTY(BlueprintAssignable)
	FOnTagChanged OnGameplayEffectStackChange;

protected:
	FAsyncTaskTagChangedData TaskData;


	virtual void OnActiveGameplayEffectAddedCallback(UAbilitySystemComponent * Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);
	virtual void OnRemoveGameplayEffectCallback(const FActiveGameplayEffect& EffectRemoved);

	virtual void GameplayEffectStackChanged(FActiveGameplayEffectHandle EffectHandle, int32 NewStackCount, int32 PreviousStackCount);
};
