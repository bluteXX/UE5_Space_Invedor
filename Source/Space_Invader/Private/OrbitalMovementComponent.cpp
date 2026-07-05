#include "OrbitalMovementComponent.h"
#include "GameFramework/Actor.h"

// ==================== Lifecycle ====================

UOrbitalMovementComponent::UOrbitalMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// ==================== Gameplay Functions ====================

void UOrbitalMovementComponent::MoveOrbit(float DeltaAngle)
{
	CurrentAngle += DeltaAngle;

	CurrentAngle = FMath::Fmod(CurrentAngle, 360.0f);
	if (CurrentAngle < 0.0f) { CurrentAngle += 360.0f; }

	UpdateOwnerPosition();
}

void UOrbitalMovementComponent::UpdateOwnerPosition()
{
	AActor* Owner = GetOwner();
	if (!Owner) return;

	float RadianAngle = FMath::DegreesToRadians(CurrentAngle);
	float NewX = OrbitRadius * FMath::Cos(RadianAngle);
	float NewZ = OrbitRadius * FMath::Sin(RadianAngle);

	FVector NewLocation(NewX, 0.0f, NewZ);
	FRotator NewRotation(CurrentAngle - 90.0f, 0.0f, 0.0f);

	Owner->SetActorLocationAndRotation(NewLocation, NewRotation);
}