// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "ProjectileActor.generated.h"

class USphereComponent;
UCLASS()
class SOULSGAME_API AProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileActor();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent * Root;

	UPROPERTY()
	USphereComponent* Base;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent * ProjectileMovement;

	UPROPERTY()
	TArray<AActor *> HitActors;
};
