#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceInvaderNormal.generated.h" 

UCLASS()
class SPACE_INVADER_API ASpaceInvaderNormal : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	void GameOver();

protected:
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Game Flow")
	void OnGameOverUI();
};