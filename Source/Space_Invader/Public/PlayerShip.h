#pragma once
#include "Damageable.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerShip.generated.h"

// Forward declarations

class UBoxComponent;
class UPaperSpriteComponent;
class UOrbitalMovementComponent;
class UWeaponComponent;
class UArrowComponent;
class UHealthComponent;
UCLASS()
class SPACE_INVADER_API APlayerShip : public APawn, public IDamageable
{
	GENERATED_BODY()

public:

	
	// Constructor & Lifecycle
	

	APlayerShip();


	virtual void BeginPlay() override;

	UFUNCTION()
	void HandlePlayerDeath();

	// Gameplay Functions

	ETeamID GetTeamID_Implementation() const;

	void TakeHit_Implementation(float Damage);

protected:


	// Input

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveAlongOrbit(float Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHealthComponent* HealthComponent;
	
	// Configuration
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float AngularSpeed = 180.0f;

	

};