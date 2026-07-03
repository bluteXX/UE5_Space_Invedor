#include "ShieldBlock.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"

AShieldBlock::AShieldBlock()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionBox->SetGenerateOverlapEvents(true);

	BlockSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BlockSprite"));
	BlockSprite->SetupAttachment(RootComponent);
}

void AShieldBlock::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void AShieldBlock::TakeHit_Implementation(float Damage)
{
	CurrentHealth -= Damage;

	if (CurrentHealth <= 0.0f)
	{
		Destroy();
		return;
	}

	
	float HealthPercent = CurrentHealth / MaxHealth;
	if (BlockSprite)
	{
		BlockSprite->SetSpriteColor(FLinearColor(1.f, 1.f, 1.f, FMath::Clamp(HealthPercent, 0.3f, 1.0f)));
	}
}

ETeamID AShieldBlock::GetTeamID_Implementation() const
{
	return ETeamID::Neutral;
}