#pragma once

#include "Damageable.h"
#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "GameTypes.h"
#include "Planet.generated.h"

class UPaperSpriteComponent;
class UHealthComponent;
class UBoxComponent;

UCLASS()
class SPACE_INVADER_API APlanet : public AActor, public IDamageable
{
	GENERATED_BODY()

public:

	APlanet();

	UFUNCTION()
	void HandlePlanetDeath();

	

	void TakeHit_Implementation(float Damage);
	ETeamID GetTeamID_Implementation() const;

protected:

	virtual void BeginPlay() override;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperSpriteComponent* PlanetSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthComponent;
};