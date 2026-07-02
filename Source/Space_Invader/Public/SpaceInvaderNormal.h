#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceInvaderNormal.generated.h" 

UCLASS()
class SPACE_INVADER_API ASpaceInvaderNormal : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	ASpaceInvaderNormal();

	
	void GameOver();

	
	void GameWon();

	
	UPROPERTY(BlueprintReadOnly, Category = "Game State")
	bool bIsGameOver = false;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Game Flow")
	void OnGameOverUI();

	
	UFUNCTION(BlueprintImplementableEvent, Category = "Game Flow")
	void OnGameWonUI();
};