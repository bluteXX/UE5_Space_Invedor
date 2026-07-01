#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerShip.generated.h"

// Forward declarations
class UBoxComponent;
class UPaperSpriteComponent;
class UOrbitalMovementComponent;
class UWeaponComponent;
class UArrowComponent;

UCLASS()
class SPACE_INVADER_API APlayerShip : public APawn
{
	GENERATED_BODY()

public:

	
	// Constructor & Lifecycle
	

	APlayerShip();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:

	
	// Actor Lifecycle
	

	virtual void BeginPlay() override;


	
	// Input
	

	
	void MoveAlongOrbit(float Value);

	void Fire();


	
	// Components
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* Muzzle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperSpriteComponent* ShipSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UOrbitalMovementComponent* OrbitalMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWeaponComponent* Weapon;


	
	// Configuration
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float AngularSpeed = 180.0f;
};