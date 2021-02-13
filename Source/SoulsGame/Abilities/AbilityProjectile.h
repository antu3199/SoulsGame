// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayMontageAbility.h"
#include "SoulsGame/Weapon/ProjectileActor.h"

#include "AbilityProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API UAbilityProjectile : public UPlayMontageAbility
{
	GENERATED_BODY()

protected:
	virtual void OnEventReceived(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AProjectileActor> ProjectileTemplate;
};

