// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MyPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API UMyPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
    UMyPrimaryDataAsset();

    // Need to create type in Project Settings/Asset Manager to be visible in editor
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Item")
    FPrimaryAssetType ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
    FText ItemName;

    // Need to override to create a unique name and be visible in editor.
    virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
