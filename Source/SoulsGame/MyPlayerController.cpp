// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AMyPlayerController::AMyPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;
    
}

void AMyPlayerController::RotateTowardsDirection()
{
    APlayerCharacter* PlayerCharacter = this->GetPawnCharacter();
    const FVector Dir = GetDirectionVector();

    FRotator ThisRotation = PlayerCharacter->GetActorRotation();

    FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, Dir);
    Rotation.Pitch = ThisRotation.Pitch;

    PlayerCharacter->SetActorRotation(Rotation);
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
}

void AMyPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    APlayerCharacter* PlayerCharacter = this->GetPawnCharacter();

    const FVector Dir = GetDirectionVector();

    if (PlayerCharacter && PlayerCharacter->OverrideRotation && Dir != FVector::ZeroVector)
    {
        FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, Dir);
        FRotator ThisRotation = PlayerCharacter->GetActorRotation();
    
        PlayerCharacter->SetActorRotation(FMath::Lerp(ThisRotation, Rotation, CharacterRotationRate));
    }

    
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
        this->OnPreInput();
        this->GetPawnCharacter()->UseAbility("Ability.Test");
    });
    this->InputComponent->KeyBindings.Add(TestAbilityBinding);
    
    FInputKeyBinding HealAbilityBinding(EKeys::H, IE_Pressed);
    HealAbilityBinding.KeyDelegate.GetDelegateForManualSet().BindLambda( [this] ()
    {
        this->OnPreInput();
        this->GetPawnCharacter()->UseAbility("Ability.Heal");
    });
    this->InputComponent->KeyBindings.Add(HealAbilityBinding);

    FInputKeyBinding TimeAbilityBinding(EKeys::G, IE_Pressed);
    TimeAbilityBinding.KeyDelegate.GetDelegateForManualSet().BindLambda( [this] ()
    {
        this->OnPreInput();
        this->GetPawnCharacter()->UseAbility("Ability.Timestop");
    });
    this->InputComponent->KeyBindings.Add(TimeAbilityBinding);

    FInputKeyBinding RollAbilityBinding(EKeys::SpaceBar, IE_Pressed);
    RollAbilityBinding.KeyDelegate.GetDelegateForManualSet().BindLambda( [this] ()
    {
        //this->GetPawnCharacter()->UseAbility("Ability.Roll");
        APlayerCharacter* Character = this->GetPawnCharacter();
        RotateTowardsDirection();
        
        Character->DoOnRoll();
        
    });
    this->InputComponent->KeyBindings.Add(RollAbilityBinding);
    
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

    if (PawnCharacter->GetCanMove())
    {
        if (InputAxis != 0)
        {
            OnPreInput();
        }
        
        PawnCharacter->AddMovementInput(Forward, InputAxis);
    }

    if (InputAxis > 0)
    {
        ForwardBackDirectionVector = Forward;
    }
    else if (InputAxis < 0)
    {
        ForwardBackDirectionVector = -Forward;
    }
    else
    {
        ForwardBackDirectionVector = FVector::ZeroVector;
    }
   
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AMyPlayerController::MoveRight(const float InputAxis)
{
    const FRotator Rotator = PlayerCameraManager->GetCameraRotation();
    const FVector Right = UKismetMathLibrary::GetRightVector(Rotator);

    APlayerCharacter* PawnCharacter = this->GetPawnCharacter();
    if (PawnCharacter->GetCanMove())
    {
        if (InputAxis != 0)
        {
            OnPreInput();
        }
        
        PawnCharacter->AddMovementInput(Right, InputAxis);
    }
    
    if (InputAxis > 0)
    {
        RightLeftDirectionVector = Right;
    }
    else if (InputAxis < 0)
    {
        RightLeftDirectionVector = -Right;
    }
    else
    {
        RightLeftDirectionVector = FVector::ZeroVector;
    }
}

FVector AMyPlayerController::GetDirectionVector() const
{
    FVector Result = (ForwardBackDirectionVector + RightLeftDirectionVector);
    Result.Z = 0;
    Result.Normalize();
        
    return Result;
}

APlayerCharacter* AMyPlayerController::GetPawnCharacter() const
{
    return Cast<APlayerCharacter>(GetPawn());
}

void AMyPlayerController::OnPreInput()
{
    APlayerCharacter* PawnCharacter = this->GetPawnCharacter();
    if (PawnCharacter == nullptr)
    {
        return;
    }

    if (PawnCharacter->JumpSectionCancellable)
    {
        PawnCharacter->StopPlayingMontage();
    }

}

// ReSharper disable once CppMemberFunctionMayBeConst
void AMyPlayerController::NormalAttack()
{

    //RotateTowardsDirection();
    this->GetPawnCharacter()->DoMeleeAttack();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AMyPlayerController::UseAbility()
{
    this->OnPreInput();
    this->GetPawnCharacter()->UseAbility("Ability.Ranged");
}


