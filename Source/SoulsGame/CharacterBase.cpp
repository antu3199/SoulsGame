// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include "GameplayTagsManager.h"
#include "MyAssetManager.h"
#include "DataAssets/AbilityAsset.h"
#include "DataAssets/WeaponAsset.h"

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
}

UWeaponAsset* ACharacterBase::GetWeaponAsset() const
{
	return this->WeaponAsset;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
    this->InitializeAbilitySystem();

	this->InitializeItems();
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

void ACharacterBase::HandleDamage(float DamageAmount, const FHitResult& HitInfo,
	const FGameplayTagContainer& DamageTags, ACharacterBase* InstigatorCharacter, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("I Got hit: %s"), *this->GetName());
	
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




