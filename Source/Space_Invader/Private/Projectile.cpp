#include "Projectile.h"

#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "Damageable.h"

// ==================== Lifecycle ====================

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;

	CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionBox->SetBoxExtent(FVector(10.0f, 10.0f, 10.0f));

	ProjectileSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ProjectileSprite"));
	ProjectileSprite->SetupAttachment(RootComponent);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(
		this,
		&AProjectile::OnOverlapBegin
	);

	SetLifeSpan(LifeSpan);
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(
		FVector(Speed * DeltaTime, 0.0f, 0.0f),
		true
	);
}

// ==================== Gameplay Functions ====================

void AProjectile::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this || OtherActor == GetOwner())
		return;

	if (!OtherActor->Implements<UDamageable>())
		return;

	ETeamID OtherTeam = IDamageable::Execute_GetTeamID(OtherActor);
	ETeamID MyTeam = ETeamID::Neutral;

	if (AActor* OwnerActor = GetOwner())
	{
		if (OwnerActor->Implements<UDamageable>())
		{
			MyTeam = IDamageable::Execute_GetTeamID(OwnerActor);
		}
	}

	if (MyTeam == OtherTeam)
		return;

	Destroy();
	IDamageable::Execute_TakeHit(OtherActor, Damage);
}