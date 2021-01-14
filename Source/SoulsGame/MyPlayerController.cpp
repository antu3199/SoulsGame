// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

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
    //this->InputComponent->BindAxis(TEXT("RotateCamera"), this, &AMyPlayerController::RotateCamera);
    //this->BindAxis(TEXT("ChangePitch"), this, &APlayerCharacter::ChangePitch);
}


void AMyPlayerController::HandleCameraRotation()
{
    const float RotateCameraValue = GetInputAxisValue(TEXT("RotateCamera"));
    const float ChangePitchValue = GetInputAxisValue(TEXT("ChangePitch"));

    this->AddYawInput(RotateCameraValue);
    this->AddPitchInput(ChangePitchValue);

    UE_LOG(LogTemp, Warning, TEXT("Bind axes camera %f"), RotateCameraValue);
    UE_LOG(LogTemp, Warning, TEXT("Bind axes pitch %f"), ChangePitchValue);
}

void AMyPlayerController::RotateCamera(float InputAxis)
{
    this->AddYawInput(InputAxis);
    UE_LOG(LogTemp, Warning, TEXT("Bind axes camera %f"), InputAxis);
}
