// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityProjectile.h"

void UAbilityProjectile::OnEventReceived(FGameplayTag GameplayTag, FGameplayEventData GameplayEventData)
{
	Super::OnEventReceived(GameplayTag, GameplayEventData);

	if (!this->ProjectileTemplate)
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile template missing!"));
		return;
	}

	/*
	const bool HasEffects = this->GameplayEffectsContainer.DoesEffectContainerHaveEffects();

	if (!HasEffects)
	{
		return;
	}
	*/

	
	AActor * AvatarActor = GetAvatarActorFromActorInfo();

	if (AvatarActor == nullptr)
	{
		return;
	}

	//Spawn Actor
	const FRotator Rotation = AvatarActor->GetActorRotation();
	const FVector Location = AvatarActor->GetActorLocation();
	const FVector Scale = FVector::OneVector;
	const FTransform Transform(Rotation,Location, Scale);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; //Default
	SpawnParameters.Instigator = Cast<APawn>(AvatarActor);

	AProjectileActor * SpawnedObject = GetWorld()->SpawnActor<AProjectileActor>(this->ProjectileTemplate, Transform, SpawnParameters);
	if (SpawnedObject)
	{
		SpawnedObject->Initialize(this);
		// Do something
	}
	
}
