// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPrimaryDataAsset.h"
#include "WeaponAsset.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API UWeaponAsset : public UMyPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// Weapon actor to spawn
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<AActor> WeaponActor;
};
