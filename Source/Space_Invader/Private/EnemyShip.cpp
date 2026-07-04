#include "EnemyShip.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "OrbitalMovementComponent.h"
#include "EnemyManager.h"
#include "WeaponComponent.h"
#include "Components/ArrowComponent.h"
#include "SpaceInvaderNormal.h"
#include "Kismet/GameplayStatics.h"
#include "GameTypes.h"

AEnemyShip::AEnemyShip()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	EnemySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("EnemySprite"));
	EnemySprite->SetupAttachment(RootComponent);

	OrbitalMovement = CreateDefaultSubobject<UOrbitalMovementComponent>(TEXT("OrbitalMovement"));

	Weapon = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon")); 
	Weapon->FireCooldown = 0.3f; 
	Weapon->bIsEnemyWeapon = true;
	

	Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(RootComponent);
	Muzzle->SetRelativeLocation(FVector(60.0f, 0.0f, 0.0f)); 
	Muzzle->SetRelativeRotation(FRotator::ZeroRotator);      
	Muzzle->ArrowSize = 1.0f; 

	
}

void AEnemyShip::TakeHit_Implementation(float Damage)
{
	
	Destroy();
}

ETeamID AEnemyShip::GetTeamID_Implementation() const
{
	return ETeamID::Enemy;
}

void AEnemyShip::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (OrbitalMovement)
	{
		OrbitalMovement->OrbitRadius = this->OrbitRadius;
		OrbitalMovement->CurrentAngle = this->StartingAngle;
		OrbitalMovement->UpdateOwnerPosition();
	}
}

void AEnemyShip::BeginPlay()
{
	Super::BeginPlay();
	Weapon->SetMuzzle(Muzzle);
}

void AEnemyShip::SetupOrbit(float NewRadius, float NewAngle)
{
	OrbitRadius = NewRadius;
	StartingAngle = NewAngle;

	if (OrbitalMovement)
	{
		OrbitalMovement->OrbitRadius = NewRadius;
		OrbitalMovement->CurrentAngle = NewAngle;
		OrbitalMovement->UpdateOwnerPosition();
	}
}

void AEnemyShip::DescendOrbit(float RadiusStep)
{
	OrbitRadius -= RadiusStep;

	RotationSpeed *= 1.2f;
	if (OrbitRadius <= DEFEAT_ORBIT_RADIUS)
	{
		if (MyManager)
		{
			MyManager->OnEnemyBreachedOrbit.Broadcast();
		}
	}

	if (OrbitalMovement)
	{
		OrbitalMovement->OrbitRadius = OrbitRadius;
		OrbitalMovement->UpdateOwnerPosition();
	}
}

void AEnemyShip::ApplySpeedMultiplier(float Multiplier)
{
	RotationSpeed *= Multiplier;
}

void AEnemyShip::Destroyed()
{
	Super::Destroyed();

	
	if (MyManager)
	{
		MyManager->RemoveEnemy(this);
	}
}


void AEnemyShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	float DeltaAngle = RotationSpeed * RotationDirection * DeltaTime;
	if (OrbitalMovement) { OrbitalMovement->MoveOrbit(DeltaAngle); }

	
	TotalAngleTraveled += FMath::Abs(DeltaAngle);

	float CurrentLaps = TotalAngleTraveled / 360.0f;

	if (CurrentLaps >= CompletedLaps + 1.0f)
	{
		
		DescendOrbit(DescendStep);
		RotationDirection *= -1.0f;

	
		CompletedLaps++;
	}
}
bool AEnemyShip::TryShoot()
{
	if (Weapon)
	{
		return Weapon->TryFire();
	}
	return false;
}