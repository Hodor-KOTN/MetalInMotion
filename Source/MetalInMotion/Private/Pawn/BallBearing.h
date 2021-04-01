#pragma once

#include "BallBearing.generated.h"

UCLASS()
class ABallBearing : public APawn
{
	GENERATED_BODY()

public:
	ABallBearing(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BallBearing);
	bool Magnetized = true;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BallBearing, meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* BallMesh;

public:
	FORCEINLINE UStaticMeshComponent* GetBallMesh() const { return BallMesh; }
	static FName BallMeshComponentName;

	virtual void DisplayDebug(UCanvas* canvas, const FDebugDisplayInfo& debugDisplay, float& yL, float& yPos) override;
	virtual void Tick(float deltaSeconds) override;
	virtual void NotifyHit(class UPrimitiveComponent* myComp, AActor* other, class UPrimitiveComponent* otherComp, bool selfMoved, FVector hitLocation, FVector hitNormal, FVector normalImpulse, const FHitResult& hit);

	UFUNCTION(BlueprintCallable)
	void ResetLocation()
	{
		BallMesh->SetWorldLocation(InitialLocation);
		BallMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
		BallMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	}

protected:
	virtual void BeginPlay() override;

protected:
	static float DebugXOffset;

	bool InContact = false;

private:
	FVector InitialLocation = FVector::ZeroVector;

};
