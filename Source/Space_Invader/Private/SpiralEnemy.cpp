#include "SpiralEnemy.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "PaperSpriteComponent.h"
#include "WeaponComponent.h"
#include "EnemyManager.h"
#include "SpaceInvaderNormal.h"
#include "Kismet/GameplayStatics.h"

ASpiralEnemy::ASpiralEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	EnemySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("EnemySprite"));
	EnemySprite->SetupAttachment(RootComponent);

	Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(RootComponent);
	Muzzle->SetRelativeLocation(FVector(60.0f, 0.0f, 0.0f));
	Muzzle->SetRelativeRotation(FRotator::ZeroRotator);
	Muzzle->ArrowSize = 1.0f;

	Weapon = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon"));
	Weapon->FireCooldown = 0.5f;
	Weapon->bIsEnemyWeapon = true;
}

void ASpiralEnemy::BeginPlay()
{
	Super::BeginPlay();

	Weapon->SetMuzzle(Muzzle);

	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ASpiralEnemy::TryFireAtCenter, FireInterval, true);
}

void ASpiralEnemy::SetupSpiral(const FVector& SpawnLocation, float InTimeToReachCenter)
{
	CurrentRadius = FMath::Sqrt(SpawnLocation.X * SpawnLocation.X + SpawnLocation.Z * SpawnLocation.Z);
	CurrentAngle = FMath::RadiansToDegrees(FMath::Atan2(SpawnLocation.Z, SpawnLocation.X));
	CenterDepth = SpawnLocation.Y;

	
	InwardSpeed = (InTimeToReachCenter > 0.0f) ? (CurrentRadius / InTimeToReachCenter) : 0.0f;

	SetActorLocation(SpawnLocation);
}

void ASpiralEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bHasBreachedOrbit)
	{
		return;
	}

	CurrentAngle += RotationSpeed * DeltaTime;
	CurrentRadius = FMath::Max(CurrentRadius - InwardSpeed * DeltaTime, 0.0f);

	float Rad = FMath::DegreesToRadians(CurrentAngle);
	FVector NewLocation(FMath::Cos(Rad) * CurrentRadius, CenterDepth, FMath::Sin(Rad) * CurrentRadius);
	SetActorLocation(NewLocation);

	
	FVector DirectionToCenter = (FVector(0.0f, CenterDepth, 0.0f) - NewLocation).GetSafeNormal();
	if (!DirectionToCenter.IsNearlyZero())
	{
		SetActorRotation(DirectionToCenter.Rotation());
	}

	
	if (CurrentRadius <= PLAYER_ORBIT_RADIUS)
	{
		OnBreachedPlayerOrbit();
	}
}

void ASpiralEnemy::TryFireAtCenter()
{
	if (Weapon && !bHasBreachedOrbit)
	{
		Weapon->TryFire();
	}
}

void ASpiralEnemy::OnBreachedPlayerOrbit()
{
	if (bHasBreachedOrbit) return;

	bHasBreachedOrbit = true;

	ASpaceInvaderNormal* GM = Cast<ASpaceInvaderNormal>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		GM->GameOver();
	}
}

void ASpiralEnemy::Destroyed()
{
	Super::Destroyed();
	GetWorldTimerManager().ClearTimer(FireTimerHandle);

	if (MyManager)
	{
		MyManager->RemoveSpiralEnemy(this);
	}
}

void ASpiralEnemy::TakeHit_Implementation(float Damage)
{
	Destroy();
}

ETeamID ASpiralEnemy::GetTeamID_Implementation() const
{
	return ETeamID::Enemy;
}