#include "Asteroid.h"
#include "Damageable.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"

// ==================== Lifecycle ====================

AAsteroid::AAsteroid()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	AsteroidSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("AsteroidSprite"));
	AsteroidSprite->SetupAttachment(RootComponent);
}

void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AAsteroid::OnAsteroidOverlap);
}

void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();
	Location.X += MoveDirection.X * MoveSpeed * DeltaTime;
	Location.Z += MoveDirection.Y * MoveSpeed * DeltaTime;
	SetActorLocation(Location);

	WrapAroundScreen();
}

// ==================== Gameplay Functions (IDamageable) ====================

void AAsteroid::TakeHit_Implementation(float Damage)
{
	if (Size != EAsteroidSize::Small)
	{
		SplitAsteroid();
	}
	Destroy();
}

ETeamID AAsteroid::GetTeamID_Implementation() const
{
	return ETeamID::Neutral;
}

// ==================== Setup ====================

void AAsteroid::InitAsteroid(const FVector2D& InDirection, float InSpeed, EAsteroidSize InSize)
{
	MoveDirection = InDirection.GetSafeNormal();
	MoveSpeed = InSpeed;
	Size = InSize;

	SetActorScale3D(FVector(GetScaleForSize(Size)));
}

// ==================== Internal Gameplay Logic ====================

float AAsteroid::GetScaleForSize(EAsteroidSize InSize) const
{
	switch (InSize)
	{
	case EAsteroidSize::Large:  return 1.5f;
	case EAsteroidSize::Medium: return 1.0f;
	case EAsteroidSize::Small:  return 0.5f;
	default: return 1.0f;
	}
}

void AAsteroid::WrapAroundScreen()
{
	FVector Location = GetActorLocation();

	if (Location.X < PLAY_FIELD_MIN_X) Location.X = PLAY_FIELD_MAX_X;
	else if (Location.X > PLAY_FIELD_MAX_X) Location.X = PLAY_FIELD_MIN_X;

	if (Location.Z < PLAY_FIELD_MIN_Z) Location.Z = PLAY_FIELD_MAX_Z;
	else if (Location.Z > PLAY_FIELD_MAX_Z) Location.Z = PLAY_FIELD_MIN_Z;

	SetActorLocation(Location);
}

void AAsteroid::SplitAsteroid()
{
	if (!AsteroidClass || !GetWorld()) return;

	EAsteroidSize NextSize = (Size == EAsteroidSize::Large) ? EAsteroidSize::Medium : EAsteroidSize::Small;

	for (int32 i = 0; i < 2; i++)
	{
		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.X += (i == 0) ? 30.0f : -30.0f;
		SpawnLocation.Z += (i == 0) ? 30.0f : -30.0f;

		FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation);

		AAsteroid* SmallerAsteroid = GetWorld()->SpawnActorDeferred<AAsteroid>(AsteroidClass, SpawnTransform);

		if (SmallerAsteroid)
		{
			float RandomAngle = FMath::FRandRange(0.0f, 360.0f);
			FVector2D RandomDir(FMath::Cos(FMath::DegreesToRadians(RandomAngle)), FMath::Sin(FMath::DegreesToRadians(RandomAngle)));

			SmallerAsteroid->InitAsteroid(RandomDir, MoveSpeed * 1.2f, NextSize);
			SmallerAsteroid->FinishSpawning(SpawnTransform);
		}
	}
}

void AAsteroid::OnAsteroidOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!OtherActor || OtherActor == this) return;

	if (OtherActor->Implements<UDamageable>())
	{
		ETeamID OtherTeam = IDamageable::Execute_GetTeamID(OtherActor);

		if (OtherTeam == ETeamID::Player)
		{
			IDamageable::Execute_TakeHit(OtherActor, ADamage);
			TakeHit_Implementation(0.0f);
		}
	}
}