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

	AShield();

protected:

	virtual void BeginPlay() override;

	void SpawnShield();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
	TSubclassOf<AShieldBlock> BlockClass;

private:

	TArray<AShieldBlock*> Blocks;
};