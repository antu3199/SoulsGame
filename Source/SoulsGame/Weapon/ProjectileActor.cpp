// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"
#include "SoulsGame/Abilities/AbilityProjectile.h"

#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);


	Base = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    Base->SetupAttachment(Root);
	Base->SetHiddenInGame(true);

	UArrowComponent * ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowComponent->SetupAttachment(Base);
    ArrowComponent->SetHiddenInGame(true);


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

}

void AProjectileActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (HitActors.Contains(OtherActor))
	{
		return;
	}

	if (OtherActor == GetInstigator())
	{
		return;
	}
	
	HitActors.Add(OtherActor);

	const TArray<FHitResult> HitResults;

	for (TSubclassOf<UMyGameplayEffect> & Effect : this->Ability->AppliedGameplayEffects)
	{
		int level = 1;

		// Bind Ability to effect
		FGameplayEffectData & Container = this->Ability->GameplayEffectsContainer.CreateNewGameplayEffectData();
		Container.GameplayEffect = Effect.GetDefaultObject();
		Container.GameplayEffectSpecHandle = this->Ability->MakeOutgoingGameplayEffectSpec(Effect, 1);

		Container.AddTargets(HitResults, HitActors);
        
		Container.ActiveGameplayEffectHandles = this->Ability->ApplyGameplayEffectSpecToTarget(Container.GameplayEffectSpecHandle, Container.TargetData);
	}
	
}

void AProjectileActor::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
}

void AProjectileActor::Initialize(UAbilityProjectile * DataContainer)
{
	this->Ability = DataContainer;
}







