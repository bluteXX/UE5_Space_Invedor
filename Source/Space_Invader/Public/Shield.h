#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shield.generated.h"

class AShieldBlock;

UCLASS()
class SPACE_INVADER_API AShield : public AActor
{
	GENERATED_BODY()

public:

	// ==================== Lifecycle ====================

	AShield();

protected:

	virtual void BeginPlay() override;

	// ==================== Internal Logic ====================

	void SpawnShield();

	// ==================== Configuration ====================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
	TSubclassOf<AShieldBlock> BlockClass;

private:

	// ==================== Runtime State ====================

	TArray<AShieldBlock*> Blocks;
};