#include "BallBearing.h"
#include "Engine/Canvas.h"
#include "DisplayDebugHelpers.h"


FName ABallBearing::BallMeshComponentName = TEXT("BallMeshComp");
float ABallBearing::DebugXOffset = 50.f;

ABallBearing::ABallBearing(const FObjectInitializer& objectInitialzier)
	:Super(objectInitialzier)
{
	PrimaryActorTick.bCanEverTick = true;

	//AutoPossessAI = EAutoPossessAI::Disabled;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(BallMeshComponentName);
	BallMesh->SetSimulatePhysics(true);
	BallMesh->SetNotifyRigidBodyCollision(true);

	SetRootComponent(BallMesh);
}

void ABallBearing::DisplayDebug(UCanvas* canvas, const FDebugDisplayInfo& debugDisplay, float& yL, float& yPos)
{
	if (debugDisplay.IsDisplayOn(TEXT("ball")))
	{
		yPos += 20.f;
		FDisplayDebugManager& dm = canvas->DisplayDebugManager;
		dm.SetDrawColor(FColor::White);
		dm.DrawString(FString::Printf(TEXT("Speed: %f"), GetVelocity().Size() / 100.f), DebugXOffset);
		dm.DrawString(FString::Printf(TEXT("InContact: %s"), InContact ? TEXT("true") : TEXT("false")), DebugXOffset);
		return;
	}

	Super::DisplayDebug(canvas, debugDisplay, yL, yPos);
}

void ABallBearing::Tick(float deltaSeconds)
{
	InContact = false;
	Super::Tick(deltaSeconds);
}

void ABallBearing::NotifyHit(class UPrimitiveComponent* myComp, AActor* other, class UPrimitiveComponent* otherComp, bool selfMoved, FVector hitLocation, FVector hitNormal, FVector normalImpulse, const FHitResult& hit)
{
	UE_LOG(LogTemp, Log, TEXT("NotifyHit %s - %s"), *GetName(), *other->GetName());
	Super::NotifyHit(myComp, other, otherComp, selfMoved, hitLocation, hitNormal, normalImpulse, hit);

	InContact = true;
}

void ABallBearing::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = BallMesh->GetComponentLocation();
	BallMesh->SetLinearDamping(.5f);
	BallMesh->SetAngularDamping(.5f);
}



