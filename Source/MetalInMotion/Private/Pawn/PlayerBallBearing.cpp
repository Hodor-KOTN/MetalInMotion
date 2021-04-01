
#include "PlayerBallBearing.h"
#include "EngineMinimal.h"
#include "GameFramework/PlayerInput.h"
#include "DisplayDebugHelpers.h"
#include "DebugUtilities.h"

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

void APlayerBallBearing::DisplayDebug(UCanvas* canvas, const FDebugDisplayInfo& debugDisplay, float& yL, float& yPos)
{
	if (debugDisplay.IsDisplayOn(TEXT("ball")))
	{
		UDebugUtilities::DrawStatistic(canvas, yPos, TEXT("Input:"), Input.ToString());
	}

	Super::DisplayDebug(canvas, debugDisplay, yL, yPos);
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
