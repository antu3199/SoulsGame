// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAnimNotifyState.h"
#include "SetCanMoveNS.generated.h"

/**
 * 
 */
UCLASS()
class SOULSGAME_API USetCanMoveNS : public UMyAnimNotifyState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	bool CanMoveNotifyStart = false;

	UPROPERTY(EditAnywhere)
	bool CanMoveNotifyEnd = true;

	UPROPERTY(EditAnywhere)
	bool CanStillRotate = true;

protected:
	virtual void DoNotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;

	virtual void DoNotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;

};
