// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAssetManager.h"
#include "AbilitySystemGlobals.h"

UMyAssetManager::UMyAssetManager()
{
}

void UMyAssetManager::StartInitialLoading()
{
    Super::StartInitialLoading();

    UAbilitySystemGlobals::Get().InitGlobalData();
}

UMyAssetManager& UMyAssetManager::Get()
{
    UMyAssetManager * AssetManager = Cast<UMyAssetManager>(GEngine->AssetManager);

    if (AssetManager)
    {
        return *AssetManager;
    }
    else
    {
        UE_LOG(LogTemp, Fatal, TEXT("AssetManager is not UMyAssetManager!"));
        return *NewObject<UMyAssetManager>();
    }
}

UObject* UMyAssetManager::ForceLoad(const FPrimaryAssetId& PrimaryAssetId)
{
    const FPrimaryAssetData * NameData = GetNameData(PrimaryAssetId);
    const FSoftObjectPath ItemPath = GetPrimaryAssetPath(PrimaryAssetId);

     // This does a synchronous load and may hitch
    return ItemPath.TryLoad();
}



