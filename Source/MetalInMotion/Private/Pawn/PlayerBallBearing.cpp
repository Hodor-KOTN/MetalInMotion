
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
	//SpringArm->SetUsingAbsoluteRotation(true);
	//SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 750.f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = false;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 20.f;
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

void APlayerBallBearing::PossessedBy(AController* controller)
{
	Super::PossessedBy(controller);
	if (controller->IsLocalPlayerController())
	{
		SetActorRotation(FRotator(-25.f, 0.f, 0.f));
		//AddControllerPitchInput(25.f);
	}
}

void APlayerBallBearing::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	check(playerInputComponent);

	playerInputComponent->BindAxis("MoveForward", this, &APlayerBallBearing::MoveForward);
	playerInputComponent->BindAxis("MoveRight", this, &APlayerBallBearing::MoveRight);
	playerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	playerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void APlayerBallBearing::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	uint64 frame = GFrameCounter;

	if (Input != FVector2D::ZeroVector)
	{
		FVector dir(Input.X, Input.Y, 0.f);
		dir.Normalize();
		dir = dir.RotateAngleAxis(GetControlRotation().Yaw, FVector::ZAxisVector);
		GetBallMesh()->AddForce(dir * ControllerForce * GetBallMesh()->GetMass());
	}
}

void APlayerBallBearing::MoveForward(float val)
{
	uint64 frame = GFrameCounter;
	Input.X = val;
}

void APlayerBallBearing::MoveRight(float val)
{
	Input.Y = val;
}
