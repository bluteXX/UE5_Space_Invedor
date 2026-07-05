#pragma once

#include "Damageable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameTypes.h"
#include "Asteroid.generated.h"

class UBoxComponent;
class UPaperSpriteComponent;

UCLASS()
class SPACE_INVADER_API AAsteroid : public AActor, public IDamageable
{
	GENERATED_BODY()

public:

	// ==================== Lifecycle ====================

	AAsteroid();

	// ==================== Gameplay Functions (IDamageable) ====================

	void TakeHit_Implementation(float Damage);
	ETeamID GetTeamID_Implementation() const;

	// ==================== Setup ====================

	void InitAsteroid(const FVector2D& InDirection, float InSpeed, EAsteroidSize InSize);

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// ==================== Internal Gameplay Logic ====================

	void WrapAroundScreen();
	void SplitAsteroid();
	float GetScaleForSize(EAsteroidSize InSize) const;

	UFUNCTION()
	virtual void OnAsteroidOverlap(AActor* OverlappedActor, AActor* OtherActor);

	// ==================== Components ====================

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperSpriteComponent* AsteroidSprite;

	// ==================== Configuration ====================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	float MoveSpeed = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	float ADamage = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	TSubclassOf<AAsteroid> AsteroidClass;

	// ==================== Runtime State ====================

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Asteroid")
	EAsteroidSize Size = EAsteroidSize::Large;

private:

	FVector2D MoveDirection = FVector2D(1.0f, 0.0f);
};