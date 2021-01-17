// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPrimaryDataAsset.h"
#include "SoulsGame/MyGameplayAbility.h"

#include "AbilityAsset.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API UAbilityAsset : public UMyPrimaryDataAsset
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
    TSubclassOf<UMyGameplayAbility> GrantedAbility;
};
