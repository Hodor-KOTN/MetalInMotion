#pragma once

#include "BallBearing.h"
#include "PlayerBallBearing.generated.h"

UCLASS()
class APlayerBallBearing : public ABallBearing
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BallBearing)
	float ControllerForce = 250.f;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta=(AllowPrivateAccess = "true"));
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"));
	class UCameraComponent* Camera;

	FVector2D Input = {0.f, 0.f};

public:
	APlayerBallBearing(const FObjectInitializer& objectInitializer = FObjectInitializer::Get());
	virtual void DisplayDebug(UCanvas* canvas, const FDebugDisplayInfo& debugDisplay, float& yL, float& yPos) override;
	virtual void PossessedBy(AController* controller);

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;
	virtual void Tick(float deltaSeconds) override;

private:
	void MoveForward(float val);
	void MoveRight(float val);


	friend class AMetalInMotionHUD;
};
