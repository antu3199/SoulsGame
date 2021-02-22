// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTaskTagChanged.h"

UAsyncTaskTagChanged* UAsyncTaskTagChanged::CreateTagChangedTask(FAsyncTaskTagChangedData& TaskData)
{
	UAsyncTaskTagChanged * MyObj = NewObject<UAsyncTaskTagChanged>();
	MyObj->TaskData = TaskData; // Copy data by value for ownership

	if (!IsValid(MyObj->TaskData.AbilitySystemComponent) || !MyObj->TaskData.EffectGameplayTag.IsValid())
	{
		MyObj->EndTask();
		return nullptr;
	}

	MyObj->TaskData.AbilitySystemComponent->RegisterGameplayTagEvent(MyObj->TaskData.EffectGameplayTag, EGameplayTagEventType::NewOrRemoved).AddUObject(MyObj, &UAsyncTaskTagChanged::TagChanged);

	return MyObj;
}

void UAsyncTaskTagChanged::EndTask()
{
	if (IsValid(TaskData.AbilitySystemComponent))
	{
		TaskData.AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.RemoveAll(this);
		TaskData.AbilitySystemComponent->OnAnyGameplayEffectRemovedDelegate().RemoveAll(this);
		TaskData.AbilitySystemComponent->RegisterGameplayTagEvent(TaskData.EffectGameplayTag, EGameplayTagEventType::NewOrRemoved).RemoveAll(this);
	}

	SetReadyToDestroy();
	MarkPendingKill();
}

void UAsyncTaskTagChanged::TagChanged(const FGameplayTag CooldownTag, int32 NewCount)
{
	ACharacterBase * Actor = Cast<ACharacterBase>(TaskData.AbilitySystemComponent->GetAvatarActor());
	if (NewCount > 0)
	{
		OnTagAdded.Broadcast(CooldownTag, NewCount, Actor);
	}
	else
	{
		OnTagRemoved.Broadcast(CooldownTag, NewCount, Actor);
		if (TaskData.DestroyOnZero)
		{
			this->EndTask();
		}
	}
}

