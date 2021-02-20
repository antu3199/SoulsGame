// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AbilityActor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"


#include "ProjectileActor.generated.h"

class UAbilityProjectile;
class USphereComponent;
UCLASS()
class SOULSGAME_API AProjectileActor : public AAbilityActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileActor();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	virtual  void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent * ProjectileMovement;

	UPROPERTY()
	TArray<AActor *> HitActors;

	UPROPERTY(EditAnywhere)
	UParticleSystem* CollisionEmitterTemplate;
};
