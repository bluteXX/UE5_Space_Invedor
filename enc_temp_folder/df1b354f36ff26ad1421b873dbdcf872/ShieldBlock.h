#pragma once

#include "Damageable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameTypes.h"
#include "ShieldBlock.generated.h"

class UBoxComponent;
class UPaperSpriteComponent;

UCLASS()
class SPACE_INVADER_API AShieldBlock : public AActor, public IDamageable
{
	GENERATED_BODY()

public:

	AShieldBlock();

	
	void TakeHit_Implementation(float Damage);
	ETeamID GetTeamID_Implementation() const;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperSpriteComponent* BlockSprite;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
	float MaxHealth = 1.0f;

private:

	float CurrentHealth = 1.0f;
};