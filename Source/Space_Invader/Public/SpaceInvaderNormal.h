#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceInvaderNormal.generated.h" 

class APawn;

UCLASS()
class SPACE_INVADER_API ASpaceInvaderNormal : public AGameModeBase
{
	GENERATED_BODY()

public:

	UFUNCTION()
	virtual void HandleEnemyBreachedOrbit();

	ASpaceInvaderNormal();
	void BeginPlay();

	void GameOver();


	void GameWon();


	UFUNCTION()
	virtual void OnPlayerDied();


	UFUNCTION()
	virtual void OnPlanetDied();


	UPROPERTY(BlueprintReadOnly, Category = "Game State")
	bool bIsGameOver = false;

protected:

	UPROPERTY()
	class AEnemyManager* EnemyManagerRef = nullptr;

	UFUNCTION()
	virtual void HandleAllEnemiesDefeated();

	void BindPlayerHealthDelegate(APawn* PlayerPawn);

	UFUNCTION(BlueprintImplementableEvent, Category = "Game Flow")
	void OnGameOverUI();


	UFUNCTION(BlueprintImplementableEvent, Category = "Game Flow")
	void OnGameWonUI();
};