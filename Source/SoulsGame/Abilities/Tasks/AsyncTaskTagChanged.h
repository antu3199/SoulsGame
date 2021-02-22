// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AbilitySystemComponent.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SoulsGame/CharacterBase.h"

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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTagChanged, FGameplayTag, Tag,  int32, NewCount, ACharacterBase *, Actor );


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
	FOnTagChanged OnTagAdded;

	UPROPERTY(BlueprintAssignable)
	FOnTagChanged OnTagRemoved;

protected:
	FAsyncTaskTagChangedData TaskData;

	virtual void TagChanged(const FGameplayTag CooldownTag, int32 NewCount);
};
