
#include "PlayerBallBearing.h"
#include "EngineMinimal.h"
#include "GameFramework/PlayerInput.h"
#include "Engine/Canvas.h"
#include "DisplayDebugHelpers.h"

APlayerBallBearing::APlayerBallBearing(const FObjectInitializer& objectInitializer)
	:Super(objectInitializer)
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 1000.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->SetupAttachment(GetBallMesh());


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void APlayerBallBearing::DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos)
{
	if (DebugDisplay.IsDisplayOn(TEXT("ball")))
	{
		YPos += 20.f;
		FDisplayDebugManager& dm = Canvas->DisplayDebugManager;
		dm.SetDrawColor(FColor::White);
		dm.DrawString(FString::Printf(TEXT("Input: %s"), *Input.ToString()), DebugXOffset);

		YPos -= 20.f; // go up 20 px cause base class has +20
	}

	Super::DisplayDebug(Canvas, DebugDisplay, YL, YPos);
}

void APlayerBallBearing::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	check(playerInputComponent);

	playerInputComponent->BindAxis("MoveForward", this, &APlayerBallBearing::MoveForward);
	playerInputComponent->BindAxis("MoveRight", this, &APlayerBallBearing::MoveRight);

}

void APlayerBallBearing::Tick(float deltaSeconds)
{
	GetBallMesh()->AddForce(FVector(Input.X, Input.Y, 0.f) * ControllerForce * GetBallMesh()->GetMass());
	Super::Tick(deltaSeconds);
}

void APlayerBallBearing::MoveForward(float val)
{
	Input.X = val;
}

void APlayerBallBearing::MoveRight(float val)
{
	Input.Y = val;
}
