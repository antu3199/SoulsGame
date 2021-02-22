// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeStopAbilityActor.h"


#include "DrawDebugHelpers.h"
#include "GameplayTagsManager.h"
#include "Camera/CameraComponent.h"
#include "SoulsGame/CharacterBase.h"
#include "SoulsGame/Abilities/Tasks/AsyncTaskTagChanged.h"
#include "Kismet/KismetSystemLibrary.h"

ATimeStopAbilityActor::ATimeStopAbilityActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATimeStopAbilityActor::Initialize(UMyGameplayAbility* DataContainer)
{
	Super::Initialize(DataContainer);

	// Allow immediately overlapping actors to trigger
	TArray<AActor *> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor *& Actor : OverlappingActors)
	{
		this->NotifyActorBeginOverlap(Actor);
	}
}

void ATimeStopAbilityActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);


	
	ACharacterBase *CharacterBase = Cast<ACharacterBase>(OtherActor);
	if (CharacterBase == nullptr || this->Ability == nullptr)
	{
		return;
	}

	if (HitActors.Contains(OtherActor))
	{
		return;
	}

	HitActors.Add(OtherActor);

	UE_LOG(LogTemp, Warning, TEXT("Apply timestop to: %s"), *OtherActor->GetName());


	TArray<AActor *> OverlappingActors {OtherActor};

	FAsyncTaskTagChangedData TaskData;
	TaskData.AbilitySystemComponent = CharacterBase->GetAbilitySystemComponent();
	TaskData.EffectGameplayTag = UGameplayTagsManager::Get().RequestGameplayTag(TEXT("State.Timestopped"));
	TaskData.DestroyOnZero = true;

	UAsyncTaskTagChanged * TagChangedTask = UAsyncTaskTagChanged::CreateTagChangedTask(TaskData);
	TagChangedTask->OnTagAdded.AddDynamic(this, &ATimeStopAbilityActor::OnTagAdded);
	TagChangedTask->OnTagRemoved.AddDynamic(this, &ATimeStopAbilityActor::OnTagRemoved);

	TagChangedTask->Activate();


	this->Ability->ApplyEffectsToActors(OverlappingActors);




}

void ATimeStopAbilityActor::NotifyActorEndOverlap(AActor* OtherActor)
{

	Super::NotifyActorEndOverlap(OtherActor);
	
	ACharacterBase *CharacterBase = Cast<ACharacterBase>(OtherActor);
	if (CharacterBase == nullptr || this->Ability == nullptr)
	{
		return;
	}

	if (HitActors.Contains(OtherActor))
	{
		HitActors.Remove(OtherActor);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("End overlap called in a non hit actor??"));
	}

	UAbilitySystemComponent * AbilitySystemComponent = CharacterBase->GetAbilitySystemComponent();
	TArray<AActor *> OverlappingActors {OtherActor};
	for (auto EffectSpec : this->Ability->GameplayEffectsContainer.ActiveGameplayEffects)
	{
		for (auto &ActiveHandle : EffectSpec.ActiveGameplayEffectHandles)
		{
			AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveHandle);
		}
	}

	UCameraComponent * CameraComponent = OtherActor->FindComponentByClass<UCameraComponent>();
	for (int i = CameraComponent->PostProcessSettings.WeightedBlendables.Array.Num()-1; i >= 0; i--)
	{
		FWeightedBlendable & BlendableWeight = CameraComponent->PostProcessSettings.WeightedBlendables.Array[i];
		if (BlendableWeight.Object->GetName() == this->InsideMaterial->GetName())
		{
			CameraComponent->PostProcessSettings.WeightedBlendables.Array.RemoveAt(i);
		}
	}
	
}

void ATimeStopAbilityActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (this->Ability == nullptr)
	{
		return;
	}

	
	const FVector CurrentScale = this->GetActorScale();
	const FVector NewScale = CurrentScale + FVector(0.1f, 0.1f, 0.1f);

	if (NewScale.X < 10)
	{
		this->SetActorScale3D(NewScale);
	}
	bool isInside = false;

	this->Base->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);





	TArray<AActor *> AllOverlappingActors;
	this->GetOverlappingActors(AllOverlappingActors);

	for (AActor * HitActor : AllOverlappingActors)
	{
		UCameraComponent * CameraComponent = HitActor->FindComponentByClass<UCameraComponent>();
		if (CameraComponent)
		{
			FVector Start = CameraComponent->GetComponentLocation(); //CameraLoc;

			FVector End = Start; //CamManager->GetCameraLocation();
			const float Radius = 10;

			const FCollisionQueryParams CollisionParms;
			TArray<FHitResult> Hits;

			const bool DidTrace = GetWorld()->SweepMultiByChannel(Hits, Start, End, FQuat::Identity, ECC_WorldDynamic, FCollisionShape::MakeSphere(Radius), CollisionParms);

			if (DidTrace)
			{
				for (FHitResult & Result : Hits)
				{
					if (Result.Actor.Get() == this)
					{
						UE_LOG(LogTemp, Warning, TEXT("Did trace"));
						isInside = true;
						break;
					}
				}
			}
			FWeightedBlendables & CurWeightedBlendables = CameraComponent->PostProcessSettings.WeightedBlendables;

			if (isInside)
			{
				UE_LOG(LogTemp, Warning, TEXT("INSIDE"));
			
				FWeightedBlendable NewBlendable;
				NewBlendable.Weight = 1;
				NewBlendable.Object = InsideMaterial;
				CameraComponent->PostProcessSettings.WeightedBlendables.Array.Add(NewBlendable);

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("NOT INSIDE"));
				// Remove current applied materials (Note: Probably inefficient. Change later...)
				for (int i = CameraComponent->PostProcessSettings.WeightedBlendables.Array.Num()-1; i >= 0; i--)
				{
					FWeightedBlendable & BlendableWeight = CameraComponent->PostProcessSettings.WeightedBlendables.Array[i];
					if (BlendableWeight.Object->GetName() == this->InsideMaterial->GetName())
					{
						CameraComponent->PostProcessSettings.WeightedBlendables.Array.RemoveAt(i);
					}
				}
					
			}

		}
	}

	this->Base->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);

}


void ATimeStopAbilityActor::OnTagAdded(const FGameplayTag CooldownTag, int32 NewCount)
{
	UE_LOG(LogTemp, Warning, TEXT("STUNNNNN"));
}

void ATimeStopAbilityActor::OnTagRemoved(const FGameplayTag CooldownTag, int32 NewCount)
{
	UE_LOG(LogTemp, Warning, TEXT("END STUN"));
}
