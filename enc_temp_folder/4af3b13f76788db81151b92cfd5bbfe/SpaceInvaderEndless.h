#pragma once

#include "CoreMinimal.h"
#include "SpaceInvaderNormal.h"
#include "SpaceInvaderEndless.generated.h"

UCLASS()
class SPACE_INVADER_API ASpaceInvaderEndless : public ASpaceInvaderNormal
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	virtual void HandleAllEnemiesDefeated() override;

	UPROPERTY()
	class AAsteroidManager* AsteroidManagerRef = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Endless")
	int32 CurrentWave = 1;
};