// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AMyPlayerController::AMyPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;
    
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
}

void AMyPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    this->UpdateRotation(DeltaTime);
}

// Tick() cannot be used to set a rotation without SetRotation()....
void AMyPlayerController::UpdateRotation(float DeltaTime)
{
    Super::UpdateRotation(DeltaTime);
    
    this->HandleCameraRotation();
}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    this->InputComponent->BindAxis(TEXT("RotateCamera"));
    this->InputComponent->BindAxis(TEXT("ChangePitch"));

    // You can do it this way, but I want to do it less segmentedly.
    this->InputComponent->BindAxis(TEXT("MoveForward"), this, &AMyPlayerController::MoveForward);
    this->InputComponent->BindAxis(TEXT("MoveRight"), this, &AMyPlayerController::MoveRight);

    this->InputComponent->BindAction("NormalAttack", IE_Pressed, this, &AMyPlayerController::NormalAttack);

    // Note: BindKey requires Slate/SlateCore
    this->InputComponent->BindKey(EKeys::F, IE_Pressed, this, &AMyPlayerController::UseAbility);

    FInputKeyBinding TestAbilityBinding(EKeys::T, IE_Pressed);
    TestAbilityBinding.KeyDelegate.GetDelegateForManualSet().BindLambda( [this] ()
    {
        this->GetPawnCharacter()->UseAbility("Ability.Test");
    });
    
    FInputKeyBinding HealAbilityBinding(EKeys::H, IE_Pressed);
    HealAbilityBinding.KeyDelegate.GetDelegateForManualSet().BindLambda( [this] ()
    {
        this->GetPawnCharacter()->UseAbility("Ability.Heal");
    });
}


void AMyPlayerController::HandleCameraRotation()
{
    const float RotateCameraValue = GetInputAxisValue(TEXT("RotateCamera"));
    const float ChangePitchValue = GetInputAxisValue(TEXT("ChangePitch"));

    this->AddYawInput(RotateCameraValue);
    this->AddPitchInput(ChangePitchValue);

    //UE_LOG(LogTemp, Warning, TEXT("Bind axes camera %f"), RotateCameraValue);
    //UE_LOG(LogTemp, Warning, TEXT("Bind axes pitch %f"), ChangePitchValue);
}

void AMyPlayerController::RotateCamera(const float InputAxis)
{
    this->AddYawInput(InputAxis);
    //UE_LOG(LogTemp, Warning, TEXT("Bind axes camera %f"), InputAxis);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AMyPlayerController::MoveForward(const float InputAxis)
{
    const FRotator Rotator = PlayerCameraManager->GetCameraRotation();
    const FVector Forward = UKismetMathLibrary::GetForwardVector(Rotator);
    APlayerCharacter* PawnCharacter = this->GetPawnCharacter();
    PawnCharacter->AddMovementInput(Forward, InputAxis);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AMyPlayerController::MoveRight(const float InputAxis)
{
    const FRotator Rotator = PlayerCameraManager->GetCameraRotation();
    const FVector Right = UKismetMathLibrary::GetRightVector(Rotator);
    APlayerCharacter* PawnCharacter = this->GetPawnCharacter();
    PawnCharacter->AddMovementInput(Right, InputAxis);
}

APlayerCharacter* AMyPlayerController::GetPawnCharacter() const
{
    return Cast<APlayerCharacter>(GetPawn());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AMyPlayerController::NormalAttack()
{
    this->GetPawnCharacter()->DoMeleeAttack();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AMyPlayerController::UseAbility()
{
    this->GetPawnCharacter()->UseAbility("Ability.Ranged");
}


