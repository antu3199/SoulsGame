// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "AbilitySystemInterface.h"
#include "Abilities/CharacterAbilitySystemComponent.h"
#include "Abilities/MyAttributeSet.h"
#include "DataAssets/WeaponAsset.h"
#include "GameFramework/Character.h"
#include "Weapon/WeaponActor.h"

#include "CharacterBase.generated.h"


class UJumpSectionNS;
// Note: IAbilitySystemInterface needed otherwise it won't listen to gameplay events
UCLASS()
class SOULSGAME_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	bool GetIsDead() const;
	
	//UPROPERTY(BlueprintReadWrite)
	//float Speed;

   // Animation blueprint property
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe)) // Needs to be BlueprintThreadSafe otherwise warning in ABP
	float GetAnimMovementSpeed() const;

	UFUNCTION(BlueprintCallable)
    void UpdateAnimMovementSpeed();

	UFUNCTION(BlueprintCallable)
    bool CanUseAnyAbility() const;

	// Calls OnDamaged in the C++ side (Done in MyAttributeSet)
	virtual void HandleDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ACharacterBase* InstigatorCharacter, AActor* DamageCauser);
	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	
	UPROPERTY(EditAnywhere, Category="Meta Data")
	FGameplayTagContainer MeleeAttackTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	TArray<FPrimaryAssetId> DefaultSlottedAbilities;


	// Handles what happens on damaged in BP size
	
	//virtual void OnDamaged(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ACharacterBase* InstigatorCharacter, AActor* DamageCauser);
	//virtual void OnHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	UWeaponAsset * GetWeaponAsset() const;

	UPROPERTY()
	AWeaponActor * WeaponActor = nullptr;

	virtual void UseAbility(const FName AbilityTag);

	virtual void MakeWeapon(const FVector Offset);


	//  Set combo, or nullptr if want to disable combo.
	void SetComboJumpSection(UJumpSectionNS * JumpSection);


	UPROPERTY(EditAnywhere, Category="Animation")
	UAnimMontage * OnHitMontage;

	UPROPERTY(EditAnywhere, Category="Socket")
	FName WeaponSocketName = TEXT("r_handSocket");

	void SetCanMove(bool Set);
	bool GetCanMove() const;

	bool OverrideRotation = true;

	bool BufferedJumpSectionCombo;

	bool JumpSectionCancellable = false;

	void TriggerJumpSectionCombo();

	void StopPlayingMontage();

	UPROPERTY(EditAnywhere)
	float CharacterOverrideRotationRate = 0.05f;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitializeAbilitySystem();
	void AddStartupGameplayAbilities();
	void InitializeItems();

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCharacterAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY()
	int32 bAbilitiesInitialized;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	FPrimaryAssetId WeaponAssetId;

	UPROPERTY()
	UWeaponAsset * WeaponAsset = nullptr;
	
	bool IsDead;
	float AnimMovementSpeed;
	TArray<FGameplayAbilitySpecHandle> AbilitiesSpecHandles;

	UPROPERTY()
	UMyAttributeSet* AttributeSet;
	
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UMyGameplayEffect>> PassiveGameplayEffects;

	UPROPERTY(EditAnywhere)
	FVector WeaponOffset;

	UPROPERTY()
	UJumpSectionNS * JumpSectionNS;

	UPROPERTY()
	UCharacterMovementComponent * CharacterMovementComponent;

	bool CanMove = true;


	
	virtual void BufferJumpSectionForCombo();
};
