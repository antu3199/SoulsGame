// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

class UCapsuleComponent;
UCLASS()
class SOULSGAME_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FGameplayTag AttackEventTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent * Root;

	bool CanHit = true;
	FTimerHandle CanHitTimer;

	void SetCanHitTimer();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent * SkeletalMeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCapsuleComponent * CapsuleComponent;

	void BeginWeaponAttack(const FGameplayTag AttackTag);

	void EndWeaponAttack();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	bool IsAttacking = false;
};
