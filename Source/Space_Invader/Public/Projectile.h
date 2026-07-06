#pragma once

#include "CoreMinimal.h"
#include "GameTypes.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UBoxComponent;
class UPaperSpriteComponent;

UCLASS()
class SPACE_INVADER_API AProjectile : public AActor
{
	GENERATED_BODY()

public:

	// ==================== Lifecycle ====================

	AProjectile();

	// ==================== Gameplay Functions ====================

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	// ==================== Components ====================

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperSpriteComponent* ProjectileSprite;

	// ==================== Configuration ====================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Speed = 1200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float LifeSpan = 3.0f;

	// ==================== Runtime State ====================

	UPROPERTY(BlueprintReadOnly, Category = "Projectile")
	bool bIsEnemyProjectile = false;

	UPROPERTY(BlueprintReadOnly, Category = "Projectile")
	ETeamID OwnerTeam = ETeamID::Neutral;

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};