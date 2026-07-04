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

	ASaveTheEarth();


	virtual void OnPlayerDied() override;

protected:

	UPROPERTY()
	class UHealthComponent* PlanetHealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = "SaveTheEarth")
	float EarthDamagePerBreach = 10.0f;

	UFUNCTION()
	void RespawnPlayer();

	virtual void HandleAllEnemiesDefeated() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
	float RespawnDelay = 5.0f;

private:
	virtual void BeginPlay() override;
	virtual void HandleEnemyBreachedOrbit() override;

	FTimerHandle RespawnTimerHandle;
};