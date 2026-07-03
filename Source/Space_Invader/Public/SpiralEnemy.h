#pragma once

#include "Damageable.h"
#include "CoreMinimal.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "GameTypes.h"
#include "SpiralEnemy.generated.h"

class UBoxComponent;
class UPaperSpriteComponent;
class UArrowComponent;
class UWeaponComponent;
class AEnemyManager;

UCLASS()
class SPACE_INVADER_API ASpiralEnemy : public AActor, public IDamageable
{
	GENERATED_BODY()

public:

	// Constructor & Lifecycle

	ASpiralEnemy();


	void SetupSpiral(const FVector& SpawnLocation, float InTimeToReachCenter);

	// Manager

	void SetManager(AEnemyManager* NewManager) { MyManager = NewManager; }

	// Gameplay Functions (IDamageable)

	void TakeHit_Implementation(float Damage);
	ETeamID GetTeamID_Implementation() const;

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;


	void OnBreachedPlayerOrbit();


	void TryFireAtCenter();

	// Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperSpriteComponent* EnemySprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* Muzzle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWeaponComponent* Weapon;

	// Configuration


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spiral")
	float RotationSpeed = 90.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float FireInterval = 2.0f;

private:

	float CurrentAngle = 0.0f;
	float CurrentRadius = 0.0f;
	float InwardSpeed = 0.0f;
	float CenterDepth = 0.0f;


	bool bHasBreachedOrbit = false;

	UPROPERTY()
	AEnemyManager* MyManager;

	FTimerHandle FireTimerHandle;
};