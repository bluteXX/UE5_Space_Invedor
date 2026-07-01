#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OrbitalMovementComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPACE_INVADER_API UOrbitalMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UOrbitalMovementComponent();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit")
	float OrbitRadius = 300.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Orbit")
	float CurrentAngle = 270.0f;

	
	UFUNCTION(BlueprintCallable, Category = "Orbit")
	void MoveOrbit(float DeltaAngle);

	
	UFUNCTION(BlueprintCallable, Category = "Orbit")
	void UpdateOwnerPosition();
};