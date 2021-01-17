// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MyAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API UMyAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
    UMyAssetManager();

    virtual void StartInitialLoading() override;

    static UMyAssetManager & Get();

    UObject * ForceLoad(const FPrimaryAssetId& PrimaryAssetId);

    template <class T>
    T * ForceLoad(const FPrimaryAssetId & PrimaryAssetId);
};

template <class T>
T* UMyAssetManager::ForceLoad(const FPrimaryAssetId& PrimaryAssetId)
{
    T * LoadedItem = Cast<T>(this->ForceLoad(PrimaryAssetId));
    if (LoadedItem == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to cast asset: %s"), *PrimaryAssetId.ToString() );
    }

    return LoadedItem;
}
