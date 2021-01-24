// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActor.h"

#include "Components/CapsuleComponent.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	this->CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	this->CapsuleComponent->SetupAttachment(Root);

	this->CapsuleComponent->IgnoreActorWhenMoving(this, true);

	this->SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	this->SkeletalMeshComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponActor::BeginWeaponAttack(const FGameplayTag AttackTag)
{
	this->AttackEventTag = AttackTag;
	this->IsAttacking = true;
	this->CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly); // No Physics collision
}

void AWeaponActor::EndWeaponAttack()
{
	this->IsAttacking = false;
	this->CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

