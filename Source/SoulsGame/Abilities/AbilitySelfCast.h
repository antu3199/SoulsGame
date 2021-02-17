// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayMontageAbility.h"
#include "AbilitySelfCast.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API UAbilitySelfCast : public UPlayMontageAbility
{
	GENERATED_BODY()

	virtual void OnEventReceived(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData) override;
	
};
