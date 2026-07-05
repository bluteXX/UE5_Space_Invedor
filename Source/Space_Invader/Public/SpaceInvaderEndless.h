#pragma once

#include "CoreMinimal.h"
#include "SpaceInvaderNormal.h"
#include "SpaceInvaderEndless.generated.h"

UCLASS()
class SPACE_INVADER_API ASpaceInvaderEndless : public ASpaceInvaderNormal
{
	GENERATED_BODY()

public:

	// ==================== Lifecycle ====================

	virtual void BeginPlay() override;

	// ==================== Runtime State ====================

	UPROPERTY(BlueprintReadOnly, Category = "Endless")
	int32 CurrentWave = 1;

protected:

	// ==================== Event Handlers ====================

	virtual void HandleAllEnemiesDefeated() override;

	// ==================== References ====================

	UPROPERTY()
	class AAsteroidManager* AsteroidManagerRef = nullptr;
};