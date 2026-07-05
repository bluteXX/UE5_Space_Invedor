#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OrbitalMovementComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPACE_INVADER_API UOrbitalMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// ==================== Lifecycle ====================

	UOrbitalMovementComponent();

	// ==================== Gameplay Functions ====================

	UFUNCTION(BlueprintCallable, Category = "Orbit")
	void MoveOrbit(float DeltaAngle);

	UFUNCTION(BlueprintCallable, Category = "Orbit")
	void UpdateOwnerPosition();

	// ==================== Configuration ====================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit")
	float OrbitRadius = 300.0f;

	// ==================== Runtime State ====================

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Orbit")
	float CurrentAngle = 270.0f;
};