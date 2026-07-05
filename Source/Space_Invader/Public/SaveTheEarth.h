#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "SpaceInvaderNormal.h"
#include "SaveTheEarth.generated.h"

UCLASS()
class SPACE_INVADER_API ASaveTheEarth : public ASpaceInvaderNormal
{
	GENERATED_BODY()

public:

	// ==================== Lifecycle ====================

	ASaveTheEarth();

	// ==================== Event Handlers ====================

	virtual void OnPlayerDied() override;

	// ==================== Configuration ====================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
	float RespawnDelay = 5.0f;

protected:

	// ==================== Event Handlers ====================

	virtual void HandleAllEnemiesDefeated() override;

	UFUNCTION()
	void RespawnPlayer();

	// ==================== References ====================

	UPROPERTY()
	class UHealthComponent* PlanetHealthComponent;

	// ==================== Configuration ====================

	UPROPERTY(EditDefaultsOnly, Category = "SaveTheEarth")
	float EarthDamagePerBreach = 10.0f;

private:

	virtual void BeginPlay() override;
	virtual void HandleEnemyBreachedOrbit() override;

	// ==================== Runtime State ====================

	FTimerHandle RespawnTimerHandle;
};