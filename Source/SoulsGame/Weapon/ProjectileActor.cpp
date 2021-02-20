// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"
#include "SoulsGame/Abilities/AbilityProjectile.h"

#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/JsonTypes.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	//Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//SetRootComponent(Root);


	UArrowComponent * ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowComponent->SetupAttachment(Base);
    ArrowComponent->SetHiddenInGame(true);


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

}

void AProjectileActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor == GetInstigator())
	{
		return;
	}

	if (OtherActor->GetOwner() == GetInstigator())
	{
		return;
	}
	
	if (HitActors.Contains(OtherActor))
	{
		return;
	}
	
	this->Base->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	
	HitActors.Add(OtherActor);


}

void AProjectileActor::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
}

void AProjectileActor::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{

	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (this->Ability == nullptr)
	{
		return;
	}

	this->Ability->ApplyEffectsToActors(HitActors);
	
	const FTransform SpawnTransform(HitLocation);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollisionEmitterTemplate, SpawnTransform, true, EPSCPoolMethod::None, true );
	this->Destroy();

	
}






