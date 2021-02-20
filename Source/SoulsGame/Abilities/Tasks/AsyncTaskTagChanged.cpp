// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTaskTagChanged.h"

UAsyncTaskTagChanged* UAsyncTaskTagChanged::CreateTagChangedTask(FAsyncTaskTagChangedData& TaskData)
{
	return nullptr;
}

void UAsyncTaskTagChanged::EndTask()
{
}

void UAsyncTaskTagChanged::OnActiveGameplayEffectAddedCallback(UAbilitySystemComponent* Target,
	const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
{
}

void UAsyncTaskTagChanged::OnRemoveGameplayEffectCallback(const FActiveGameplayEffect& EffectRemoved)
{
}

void UAsyncTaskTagChanged::GameplayEffectStackChanged(FActiveGameplayEffectHandle EffectHandle, int32 NewStackCount,
	int32 PreviousStackCount)
{
}
