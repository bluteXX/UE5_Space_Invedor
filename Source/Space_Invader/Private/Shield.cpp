#include "Shield.h"
#include "ShieldBlock.h"
#include "Components/BoxComponent.h"

AShield::AShield()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void AShield::BeginPlay()
{
	Super::BeginPlay();
	SpawnShield();
}

void AShield::SpawnShield()
{
	if (!BlockClass || !GetWorld()) return;

	float BlockWidth = 32.0f;
	float BlockHeight = 32.0f;

	

	AShieldBlock* DefaultBlock = Cast<AShieldBlock>(BlockClass->GetDefaultObject());
	if (DefaultBlock)
	{
		if (UBoxComponent* BoxComp = Cast<UBoxComponent>(DefaultBlock->GetRootComponent()))
		{
			
			FVector UnscaledExtent = BoxComp->GetUnscaledBoxExtent();

		
			FVector ComponentScale = BoxComp->GetRelativeScale3D();

	
			BlockWidth = (UnscaledExtent.X * ComponentScale.X) * 2.0f;
			BlockHeight = (UnscaledExtent.Z * ComponentScale.Z) * 2.0f;
		}
	}

	static const TArray<TArray<int32>> ShieldPattern = {
		{0,1,1,1,1,1,1,0},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,0,0,1,1,1},
		{1,1,0,0,0,0,1,1},
	};

	for (int32 Row = 0; Row < ShieldPattern.Num(); Row++)
	{
		for (int32 Col = 0; Col < ShieldPattern[Row].Num(); Col++)
		{
			if (ShieldPattern[Row][Col] == 0) continue;

			
			FVector SpawnLocation = GetActorLocation() + FVector(Col * BlockWidth, 0.f, -Row * BlockHeight);

			AShieldBlock* NewBlock = GetWorld()->SpawnActor<AShieldBlock>(BlockClass, SpawnLocation, FRotator::ZeroRotator);
			if (NewBlock)
			{
				Blocks.Add(NewBlock);
			}
		}
	}
}