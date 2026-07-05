#include "Planet.h"
#include "PaperSpriteComponent.h"
#include "HealthComponent.h"
#include "SpaceInvaderNormal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"

// ==================== Lifecycle ====================

APlanet::APlanet()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionBox->SetGenerateOverlapEvents(true);

	PlanetSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PlanetSprite"));
	PlanetSprite->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void APlanet::BeginPlay()
{
	Super::BeginPlay();

	if (HealthComponent)
	{
		HealthComponent->OnDeath.AddDynamic(this, &APlanet::HandlePlanetDeath);
	}
}

// ==================== Gameplay Functions (IDamageable) ====================

void APlanet::TakeHit_Implementation(float Damage)
{
	if (HealthComponent)
	{
		HealthComponent->ApplyDamage(Damage);
	}
}

ETeamID APlanet::GetTeamID_Implementation() const
{
	return ETeamID::Player;
}

// ==================== Event Handlers ====================

void APlanet::HandlePlanetDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Wizualny wybuch planety!"));
	Destroy();
}