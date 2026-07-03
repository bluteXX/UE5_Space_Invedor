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

	

	AAsteroid();

	
	void InitAsteroid(const FVector2D& InDirection, float InSpeed, EAsteroidSize InSize);

	

	void TakeHit_Implementation(float Damage);
	ETeamID GetTeamID_Implementation() const;

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void WrapAroundScreen();
	void SplitAsteroid();
	float GetScaleForSize(EAsteroidSize InSize) const;

	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperSpriteComponent* AsteroidSprite;

	UFUNCTION()
	virtual void OnAsteroidOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	float MoveSpeed = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	float ADamage = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	TSubclassOf<AAsteroid> AsteroidClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Asteroid")
	EAsteroidSize Size = EAsteroidSize::Large;

private:

	
	FVector2D MoveDirection = FVector2D(1.0f, 0.0f);
};