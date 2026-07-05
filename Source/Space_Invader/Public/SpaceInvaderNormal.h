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

	// ==================== Lifecycle ====================

	ASpaceInvaderNormal();
	void BeginPlay();

	// ==================== Game Flow ====================

	void GameOver();
	void GameWon();

	// ==================== Event Handlers ====================

	UFUNCTION()
	virtual void OnPlayerDied();

	UFUNCTION()
	virtual void OnPlanetDied();

	UFUNCTION()
	virtual void HandleEnemyBreachedOrbit();

	// ==================== Runtime State ====================

	UPROPERTY(BlueprintReadOnly, Category = "Game State")
	bool bIsGameOver = false;

protected:

	// ==================== References ====================

	UPROPERTY()
	class AEnemyManager* EnemyManagerRef = nullptr;

	// ==================== Internal Logic ====================

	UFUNCTION()
	virtual void HandleAllEnemiesDefeated();

	void BindPlayerHealthDelegate(APawn* PlayerPawn);

	// ==================== Blueprint UI Hooks ====================

	UFUNCTION(BlueprintImplementableEvent, Category = "Game Flow")
	void OnGameOverUI();

	UFUNCTION(BlueprintImplementableEvent, Category = "Game Flow")
	void OnGameWonUI();
};