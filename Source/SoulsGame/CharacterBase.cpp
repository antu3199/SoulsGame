// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include "GameplayTagsManager.h"
#include "MyAssetManager.h"
#include "DataAssets/AbilityAsset.h"
#include "DataAssets/WeaponAsset.h"
#include "Animation/JumpSectionNS.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"



// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UCharacterAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	if (MeleeAttackTag.Num() == 0)
	{
		FGameplayTag Tag = UGameplayTagsManager::Get().RequestGameplayTag(TEXT("Ability.Melee"));
		MeleeAttackTag.AddTag(Tag);
		//UE_LOG(LogTemp, Error, TEXT("ERROR: Melee attack tag not created!"));
	}

	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));

	CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetComponentByClass(UCharacterMovementComponent::StaticClass()));
}

UWeaponAsset* ACharacterBase::GetWeaponAsset() const
{
	return this->WeaponAsset;
}

void ACharacterBase::SetCanMove(bool Set)
{
	CanMove = Set;
}

bool ACharacterBase::GetCanMove() const
{
	return CanMove;
}

bool ACharacterBase::TriggerJumpSectionCombo()
{
	if (this->JumpSectionNS == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("TriggerJumpSection failed:no JUmpSectioNS!"));
		return false;
	}

	if (!GetMesh())
	{
		return false;
	}

	UAnimInstance * AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance)
	{
		UE_LOG(LogTemp, Display, TEXT("TriggerJumpSection failed: no anim instance!"));
		return false;
	}

	UAnimMontage * CurrentActiveMontage = AnimInstance->GetCurrentActiveMontage();
	if (!CurrentActiveMontage)
	{
		UE_LOG(LogTemp, Display, TEXT("TriggerJumpSection failed: no current montage!" ));
		return false;
	}

	if (BufferedInput.InputType != EBufferedInputType::Attack)
	{
		// Ignore input failures
		UE_LOG(LogTemp, Display, TEXT("TriggerJumpSection failed: Buffered input incorrect!!"));
		return false;
	}

	const FName CurrentSectionName = AnimInstance->Montage_GetCurrentSection(CurrentActiveMontage);

	const int RandInt = FMath::RandRange(0, this->JumpSectionNS->NextMontageNames.Num() - 1);
	const FName NextSectionName = this->JumpSectionNS->NextMontageNames[RandInt];

	// Wait till animation finishes
	//AnimInstance->Montage_SetNextSection(CurrentSectionName, NextSectionName, CurrentActiveMontage);

	// Jumps directly to animation
	AnimInstance->Montage_JumpToSection(NextSectionName, CurrentActiveMontage);


	// Hack to blend two montages. Works out of the box, but need to fix callback logic...

	/*
	FName NewMontageGroupName = CurrentActiveMontage->GetGroupName();

	TPair<FOnMontageEnded, FOnMontageBlendingOutStarted> CallbackPair;
	
	for (int32 InstanceIndex = 0; InstanceIndex < AnimInstance->MontageInstances.Num(); InstanceIndex++)
	{
		FAnimMontageInstance* MontageInstance = AnimInstance->MontageInstances[InstanceIndex];
		if (MontageInstance && MontageInstance->Montage && (MontageInstance->Montage->GetGroupName() == NewMontageGroupName))
		{
			CallbackPair = TPairInitializer<FOnMontageEnded, FOnMontageBlendingOutStarted>(MontageInstance->OnMontageEnded, MontageInstance->OnMontageBlendingOutStarted);
			MontageInstance->OnMontageEnded.Unbind();
			MontageInstance->OnMontageBlendingOutStarted.Unbind();
		}
	}

	CurrentActiveMontage->AddMetaData(nullptr);
	
	AnimInstance->Montage_Play(CurrentActiveMontage);
	
	for (int32 InstanceIndex = 0; InstanceIndex < AnimInstance->MontageInstances.Num(); InstanceIndex++)
	{
		FAnimMontageInstance* MontageInstance = AnimInstance->MontageInstances[InstanceIndex];
		if (MontageInstance && MontageInstance->Montage && (MontageInstance->Montage->GetGroupName() == NewMontageGroupName))
		{
			MontageInstance->OnMontageEnded = CallbackPair.Key;
			MontageInstance->OnMontageBlendingOutStarted = CallbackPair.Value;
		}
	}

	AnimInstance->Montage_JumpToSection(NextSectionName, CurrentActiveMontage);
*/

	
	//UE_LOG(LogTemp, Warning, TEXT("Trigger section %s"), *NextSectionName.ToString());
	this->JumpSectionNS = nullptr;
	BufferedInput.Reset();
	UE_LOG(LogTemp, Display, TEXT("BufferedJumpSectionCombo Set to false"));
	JumpSectionCancellable = false;
	return true;
}

void ACharacterBase::StopPlayingMontage()
{
	UAnimInstance * AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance)
	{
		return;
	}

	UAnimMontage * CurrentActiveMontage = AnimInstance->GetCurrentActiveMontage();
	if (!CurrentActiveMontage)
	{
		return;
	}
	
	AnimInstance->Montage_Stop(0.1f, CurrentActiveMontage);
	this->JumpSectionCancellable = false;
}

void ACharacterBase::CheckBufferedInput()
{
	if (!JumpSectionCancellable)
	{
		return;
	}
    
	if (BufferedInput.InputType == EBufferedInputType::Attack)
	{
		UE_LOG(LogTemp, Warning, TEXT("DO ATTACK!"));
		TriggerJumpSectionCombo();
	}

}

void ACharacterBase::DoOnRoll()
{
	if (!this->AbilitySystemComponent)
	{
		return;
	}
    
	if (!this->CanUseAnyAbility())
	{
		return;
	}

	if (this->OnRollMontage == nullptr)
	{
		return;
	}


	//FRotator ControlRotation = GetControlRotation(); // Control rotation is the camera, but I don't want this.
	//SetActorRotation(ControlRotation);
    

	//FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, Right);
	//    PawnCharacter->SetActorRotation(Rotation);

    
	UAnimInstance * AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance)
	{
		return;
	}


	AnimInstance->Montage_Play(OnRollMontage);

}

bool ACharacterBase::GetRootMotionEnabled() const
{
	UAnimInstance * AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance)
	{
		return false;
	}

	FAnimMontageInstance* MontageInstance = AnimInstance->GetActiveMontageInstance();
	if (!MontageInstance)
	{
		return false;
	}

	return !MontageInstance->IsRootMotionDisabled();
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
    this->InitializeAbilitySystem();

	this->InitializeItems();

	this->MakeWeapon(WeaponOffset);
}

void ACharacterBase::InitializeAbilitySystem()
{

	if (this->AbilitySystemComponent)
	{
		this->AbilitySystemComponent->InitAbilityActorInfo(this, this);
		this->AddStartupGameplayAbilities();
	}
}

void ACharacterBase::AddStartupGameplayAbilities()
{
	if (!this->AbilitySystemComponent)
	{
		return;
	}
	
	if (this->AbilitiesSpecHandles.Num() != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning: Ability spec handles not empty"));
	}

	UMyAssetManager & MyAssetManager = UMyAssetManager::Get();

	for (const FPrimaryAssetId & AssetId : this->DefaultSlottedAbilities)
	{
		UAbilityAsset * ItemAsset = MyAssetManager.ForceLoad<UAbilityAsset>(AssetId);
		if (ItemAsset)
		{
			//this->AbilitiesSpecHandles.Add
			FGameplayAbilityDataContainer & DataContainer = this->AbilitySystemComponent->AddNewGameplayAbilityDataContainer(); 
			DataContainer.SetGameplayAbility(ItemAsset->GrantedAbility.GetDefaultObject());
			DataContainer.GameplayAbilitySpec = FGameplayAbilitySpec(DataContainer.MyGameplayAbility);
			DataContainer.GameplayAbilitySpecHandle = this->AbilitySystemComponent->GiveAbility(DataContainer.GameplayAbilitySpec);

			UE_LOG(LogTemp, Warning, TEXT("Ability granted %s"), *DataContainer.GetMyGameplayAbilityName());
		}
	}

	
	for (TSubclassOf<UMyGameplayEffect> & Effect : PassiveGameplayEffects)
	{
		this->AbilitySystemComponent->ApplyGameplayEffect(Effect, this);
	}
}

void ACharacterBase::InitializeItems()
{
	// Load items
	// 
	// Load weapon
	UMyAssetManager & MyAssetManager = UMyAssetManager::Get();
	UWeaponAsset * TheAsset = MyAssetManager.ForceLoad<UWeaponAsset>(this->WeaponAssetId);
	if (TheAsset)
	{
		this->WeaponAsset = TheAsset;
		UE_LOG(LogTemp, Warning, TEXT("Weapon granted %s"), *WeaponAsset->ItemName.ToString());
	}
}

bool ACharacterBase::IsAttacking() const
{
	const FName MeleeAbilityTag = "Ability.Melee";

	return this->AbilitySystemComponent->IsUsingAbilityWithTag(MeleeAbilityTag);
}

void ACharacterBase::BufferJumpSectionForCombo()
{
	if (this->JumpSectionNS == nullptr)
	{
		return;
	}

	if (!GetMesh())
	{
		return;
	}

	UAnimInstance * AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance)
	{
	    return;
	}

	UAnimMontage * CurrentActiveMontage = AnimInstance->GetCurrentActiveMontage();
    if (!CurrentActiveMontage)
    {
	    return;
    }

	this->BufferedInput.SetBufferedAttackInput();

	UE_LOG(LogTemp, Display, TEXT("BufferedJumpSectionCombo Set to true"));

}

// Called every frame
void ACharacterBase::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return this->AbilitySystemComponent;
}

bool ACharacterBase::GetIsDead() const
{
	return this->IsDead;
}

float ACharacterBase::GetAnimMovementSpeed() const
{
	return this->AnimMovementSpeed;
}

void ACharacterBase::UpdateAnimMovementSpeed()
{
	const FVector Velocity = this->GetVelocity();
	const float NormalizedVelocity = Velocity.Size();

	this->AnimMovementSpeed = NormalizedVelocity;
}

bool ACharacterBase::CanUseAnyAbility() const
{
	return !this->IsDead;
}

bool ACharacterBase::CanInputAnyAbility() const
{
	return !IsPlayingRootMotion();
}

void ACharacterBase::HandleDamage(float DamageAmount, const FHitResult& HitInfo,
                                  const FGameplayTagContainer& DamageTags, ACharacterBase* InstigatorCharacter, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("I Got hit: %s"), *this->GetName());
	if (this->OnHitMontage != nullptr)
	{
		UAnimInstance * AnimInstance = GetMesh()->GetAnimInstance();
		if (!AnimInstance)
		{
			return;
		}


		const FName CurrentSectionName = AnimInstance->Montage_GetCurrentSection(OnHitMontage);

		const int RandInt = FMath::RandRange(0, OnHitMontage->CompositeSections.Num() - 1);
		const FName NextSectionName = OnHitMontage->GetSectionName(RandInt);

		AnimInstance->Montage_Play(OnHitMontage);
		AnimInstance->Montage_JumpToSection(NextSectionName, OnHitMontage);
	}

	bool FaceAttacker = true;
	if (FaceAttacker)
	{
		FVector MyLocation = GetActorLocation();

		FVector InstigatorLocation = InstigatorCharacter->GetActorLocation();
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(MyLocation, InstigatorLocation);
		FRotator ThisRotation = this->GetActorRotation();

		Rotation.Pitch = ThisRotation.Pitch;

		//FVector RotationEuler = Rotation.Euler();
		//RotationEuler.Y = ThisRotation.Euler().Y;
		//FRotator FinalRotation = FRotator::MakeFromEuler(RotationEuler);

		SetActorRotation(Rotation);
	}
	
	
	//this->OnDamaged(DamageAmount, HitInfo, DamageTags, InstigatorCharacter, DamageCauser);
}

void ACharacterBase::HandleHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags)
{
	UE_LOG(LogTemp, Warning, TEXT("Handle health changed: %s"), *EventTags.ToString());

	if (this->bAbilitiesInitialized)
	{
		//this->OnHealthChanged(DeltaValue, EventTags);
	}
}

void ACharacterBase::UseAbility(const FName AbilityTag)
{
	if (!this->AbilitySystemComponent)
	{
		return;
	}

	if (this->AbilitySystemComponent->ActivateAbilityWithTag(AbilityTag))
	{
		// UE_LOG(LogTemp, Warning, TEXT("Activate ability %s"), *AbilityTag.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter::DoRangedAttack SUCCESSED!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to activate ability %s"), *AbilityTag.ToString());
	}
}

void ACharacterBase::MakeWeapon(const FVector Offset)
{
	if (this->WeaponAsset == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No weapon found!"));
		return;
	}
	const FRotator Rotation = FRotator::ZeroRotator;
	const FVector Location(Offset);
	const FVector Scale = FVector::OneVector;
	const FTransform Transform(Rotation,Location, Scale);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined; //Default
	SpawnParameters.Instigator = this; // Needed for WeaponActor.cpp
	SpawnParameters.Owner = this;


	AActor * SpawnedObject = GetWorld()->SpawnActor<AActor>(this->WeaponAsset->WeaponActorTemplate, Location, Rotation, SpawnParameters);
	if (SpawnedObject)
	{
		//this->AttachToComponent(this->GetMesh(), SpawnedObject,
		const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true );
		const FName SocketName = this->WeaponSocketName;
		SpawnedObject->AttachToComponent(this->GetMesh(), AttachmentRules, SocketName);

		this->WeaponActor = Cast<AWeaponActor>(SpawnedObject);
		if (this->WeaponActor == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Weapon was null!"));
		}
	}
}

void ACharacterBase::SetComboJumpSection(UJumpSectionNS* JumpSection)
{
	this->JumpSectionNS = JumpSection;

	if (JumpSection != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set jump section %s"), *JumpSection->NextMontageNames[0].ToString() );
	}
	
	//this->BufferedJumpSectionCombo = false; // Not necessary, but just in case

}


// ================= Buffered input:

void FBufferedInput::SetBufferedAttackInput()
{
	//if ((int) EBufferedInputType::Attack < (int)InputType)
	//{
	//	return;
	//}

	InputType = EBufferedInputType::Attack;
}

void FBufferedInput::SetBufferedRollInput()
{
	if ((int) EBufferedInputType::Roll < (int)InputType)
	{
		return;
	}

	InputType = EBufferedInputType::Roll;
}

void FBufferedInput::SetBufferedAbilityInput()
{
	if ((int) EBufferedInputType::Ability < (int)InputType)
	{
		return;
	}

	InputType = EBufferedInputType::Ability;
}

void FBufferedInput::Reset()
{
	InputType = EBufferedInputType::None;
	
}