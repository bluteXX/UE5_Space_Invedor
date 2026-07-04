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

	const TArray<TArray<int32>> ShieldPattern = {
		{0,0,0,1,1,0,0,0},
		{0,0,1,1,1,1,0,0},
		{0,1,1,1,1,1,1,0},
	};

	
	if (ShieldPattern.Num() == 0 || ShieldPattern[0].Num() == 0) return;

	
	int32 NumRows = ShieldPattern.Num();
	int32 NumCols = ShieldPattern[0].Num();


	float CenterOffsetX = (NumCols - 1) * BlockWidth / 2.0f;
	float CenterOffsetZ = (NumRows - 1) * BlockHeight / 2.0f;

	for (int32 Row = 0; Row < NumRows; Row++)
	{
		for (int32 Col = 0; Col < NumCols; Col++)
		{
			if (ShieldPattern[Row][Col] == 0) continue;

			
			float LocalX = (Col * BlockWidth) - CenterOffsetX;
			
			float LocalZ = (-Row * BlockHeight) + CenterOffsetZ;

			FVector LocalOffset = FVector(LocalX, 0.f, LocalZ);

			
			FVector SpawnLocation = GetActorLocation() + GetActorRotation().RotateVector(LocalOffset);

			AShieldBlock* NewBlock = GetWorld()->SpawnActor<AShieldBlock>(BlockClass, SpawnLocation, GetActorRotation());

			if (NewBlock)
			{
				NewBlock->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
				Blocks.Add(NewBlock);
			}
		}
	}
}