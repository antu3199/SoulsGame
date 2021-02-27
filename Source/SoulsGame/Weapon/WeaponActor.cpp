// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActor.h"



#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Chaos/GeometryParticlesfwd.h"
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

void AWeaponActor::SetCanHitTimer()
{
	this->CanHit = true;
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
	this->CanHit = true;
	if (GetWorld())
	{
    	FTimerManager &WorldTimerManager = GetWorldTimerManager();
    	WorldTimerManager.ClearTimer(CanHitTimer);
	}

	this->CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly); // No Physics collision
}

void AWeaponActor::EndWeaponAttack()
{
	this->IsAttacking = false;
	this->CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

void AWeaponActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// Tests to check if you can collide with it.
	// Probably want to override this later...
	AActor * InstigatorActor = GetInstigator();
	if (InstigatorActor == nullptr || OtherActor == nullptr)
	{
		return;
	}
	
	if (InstigatorActor->GetClass() == OtherActor->GetClass())
	{
		return;
	}

	if (this->IsAttacking == false)
	{
		return;
	}

	if (!this->CanHit)
	{
		return;
	}


	this->CanHit = false;

	FGameplayEventData GameplayEventData;
	GameplayEventData.Instigator = InstigatorActor;
	GameplayEventData.Target = OtherActor;

	UE_LOG(LogTemp, Warning, TEXT("Send gameplay event to actor %s Target: %s"), *InstigatorActor->GetName(), *OtherActor->GetName());
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(InstigatorActor, this->AttackEventTag, GameplayEventData);
}

void AWeaponActor::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (this->CanHit && GetWorld())
	{
		GetWorldTimerManager().SetTimer(CanHitTimer, this, &AWeaponActor::SetCanHitTimer,2.f /*Time you want*/, false /*if you want loop set to true*/);
	}
}

