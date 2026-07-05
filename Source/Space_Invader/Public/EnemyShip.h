#pragma once

#include "Damageable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyShip.generated.h"

class UArrowComponent;
class UBoxComponent;
class UPaperSpriteComponent;
class UOrbitalMovementComponent;
class UWeaponComponent;
class AEnemyManager;

UCLASS()
class SPACE_INVADER_API AEnemyShip : public AActor, public IDamageable
{
	GENERATED_BODY()

public:

	// ==================== Lifecycle ====================

	AEnemyShip();
	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void Destroyed() override;

	// ==================== Gameplay Functions (IDamageable) ====================
	
	void TakeHit_Implementation(float Damage);

	virtual ETeamID GetTeamID_Implementation() const override;

	// ==================== Gameplay Functions ====================

	void SetupOrbit(float NewRadius, float NewAngle);
	void DescendOrbit(float RadiusStep);
	bool TryShoot();

	UFUNCTION()
	void ApplySpeedMultiplier(float Multiplier);

	// ==================== Manager ====================

	void SetManager(AEnemyManager* NewManager) { MyManager = NewManager; }
	void SetDescendStep(float NewStep) { DescendStep = NewStep; }

	// ==================== Configuration ====================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float OrbitRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float StartingAngle = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float RotationSpeed = 20.0f;

	// ==================== Runtime State ====================

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float RotationDirection = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	float DescendStep = 100.0f;

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// ==================== Components ====================

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperSpriteComponent* EnemySprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UOrbitalMovementComponent* OrbitalMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWeaponComponent* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* Muzzle;

private:

	// ==================== References ====================

	UPROPERTY()
	AEnemyManager* MyManager;

	// ==================== Runtime State ====================

	float TotalAngleTraveled = 0.0f;
	int32 CompletedLaps = 0;
};