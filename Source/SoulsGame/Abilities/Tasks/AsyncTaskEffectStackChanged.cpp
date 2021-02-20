// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTaskEffectStackChanged.h"

UAsyncTaskEffectStackChanged* UAsyncTaskEffectStackChanged::CreateGameplayEffectStackChangedTask(
	FAsyncTaskEffectStackChangedData& TaskData)
{
	UAsyncTaskEffectStackChanged * MyObj = NewObject<UAsyncTaskEffectStackChanged>();
	MyObj->TaskData = TaskData; // Copy data by value for ownership

	if (!IsValid(MyObj->TaskData.AbilitySystemComponent) || !MyObj->TaskData.EffectGameplayTag.IsValid())
	{
		MyObj->EndTask();
		return nullptr;
	}

	MyObj->TaskData.AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(MyObj, &UAsyncTaskEffectStackChanged::OnActiveGameplayEffectAddedCallback);
	MyObj->TaskData.AbilitySystemComponent->OnAnyGameplayEffectRemovedDelegate().AddUObject(MyObj, &UAsyncTaskEffectStackChanged::OnRemoveGameplayEffectCallback);

	return MyObj;
}

void UAsyncTaskEffectStackChanged::EndTask()
{
	if (IsValid(TaskData.AbilitySystemComponent))
	{
		TaskData.AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.RemoveAll(this);
		TaskData.AbilitySystemComponent->OnAnyGameplayEffectRemovedDelegate().RemoveAll(this);
	}

	SetReadyToDestroy();
	MarkPendingKill();
}

void UAsyncTaskEffectStackChanged::OnActiveGameplayEffectAddedCallback(UAbilitySystemComponent* Target,
	const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
{
	FGameplayTagContainer AssetTags;
	SpecApplied.GetAllAssetTags(AssetTags);

	FGameplayTagContainer GrantedTags;
	SpecApplied.GetAllGrantedTags(GrantedTags);

	if (AssetTags.HasTagExact(TaskData.EffectGameplayTag) || GrantedTags.HasTagExact(TaskData.EffectGameplayTag))
	{
		TaskData.AbilitySystemComponent->OnGameplayEffectStackChangeDelegate(ActiveHandle)->AddUObject(this, &UAsyncTaskEffectStackChanged::GameplayEffectStackChanged);
		OnGameplayEffectStackChange.Broadcast(TaskData.EffectGameplayTag, ActiveHandle, 1, 0);
	}
}

void UAsyncTaskEffectStackChanged::OnRemoveGameplayEffectCallback(const FActiveGameplayEffect& EffectRemoved)
{
	FGameplayTagContainer AssetTags;
	EffectRemoved.Spec.GetAllAssetTags(AssetTags);

	FGameplayTagContainer GrantedTags;
	EffectRemoved.Spec.GetAllGrantedTags(GrantedTags);

	if (AssetTags.HasTagExact(TaskData.EffectGameplayTag) || GrantedTags.HasTagExact(TaskData.EffectGameplayTag))
	{
		OnGameplayEffectStackChange.Broadcast(TaskData.EffectGameplayTag, EffectRemoved.Handle, 0, 1);

		if (TaskData.DestroyOnZero)
		{
			this->EndTask();
		}
	}
}

void UAsyncTaskEffectStackChanged::GameplayEffectStackChanged(FActiveGameplayEffectHandle EffectHandle,
	int32 NewStackCount, int32 PreviousStackCount)
{
	OnGameplayEffectStackChange.Broadcast(TaskData.EffectGameplayTag, EffectHandle, NewStackCount, PreviousStackCount);
}


