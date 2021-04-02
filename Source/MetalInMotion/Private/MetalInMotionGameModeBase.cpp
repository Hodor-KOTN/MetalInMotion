// Copyright Epic Games, Inc. All Rights Reserved.

#include "MetalInMotionGameModeBase.h"

AMetalInMotionGameModeBase::AMetalInMotionGameModeBase()
{
}

void AMetalInMotionGameModeBase::FinishRestartPlayer(AController* playerController, const FRotator& startRotation)
{
	FRotator controlRotation = startRotation;
	controlRotation.Pitch = -30.f;
	Super::FinishRestartPlayer(playerController, controlRotation);
}

