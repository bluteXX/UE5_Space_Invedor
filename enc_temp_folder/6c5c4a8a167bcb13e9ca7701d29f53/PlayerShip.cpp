#include "PlayerShip.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "OrbitalMovementComponent.h"
#include "HealthComponent.h"
#include "WeaponComponent.h" 
#include "Components/ArrowComponent.h"
#include "SpaceInvaderNormal.h"
#include "Kismet/GameplayStatics.h"
APlayerShip::APlayerShip()
{
	PrimaryActorTick.bCanEverTick = false; 

	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	
	ShipSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ShipSprite"));
	ShipSprite->SetupAttachment(RootComponent);

	
	OrbitalMovement = CreateDefaultSubobject<UOrbitalMovementComponent>(TEXT("OrbitalMovement"));

	Weapon = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon")); 
	Weapon->FireCooldown = 0.5f;
	Weapon->bIsEnemyWeapon = false;

	Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(RootComponent);
	Muzzle->SetRelativeLocation(FVector(60.0f, 0.0f, 0.0f)); 
	Muzzle->SetRelativeRotation(FRotator::ZeroRotator);      
	Muzzle->ArrowSize = 1.0f; 
	

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	
	
}

void APlayerShip::BeginPlay()
{
	Super::BeginPlay();
	Weapon->SetMuzzle(Muzzle);
	
	if (OrbitalMovement)
	{
		OrbitalMovement->UpdateOwnerPosition();
	}
	if (HealthComponent)
	{
		HealthComponent->OnDeath.AddDynamic(this, &APlayerShip::HandlePlayerDeath);
	}
}

void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
	PlayerInputComponent->BindAxis("MoveAlongOrbit", this, &APlayerShip::MoveAlongOrbit);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerShip::Fire); 
}

void APlayerShip::MoveAlongOrbit(float Value)
{
	if (Value != 0.0f && OrbitalMovement != nullptr)
	{
		
		float DeltaAngle = Value * AngularSpeed * GetWorld()->GetDeltaSeconds();

		
		OrbitalMovement->MoveOrbit(DeltaAngle);
	}
}
void APlayerShip::Fire()
{
	if (Weapon)
	{
		Weapon->TryFire();
	}
}

ETeamID APlayerShip::GetTeamID_Implementation() const
{
	return ETeamID::Player;
}

void APlayerShip::TakeHit_Implementation(float Damage)
{
	if (HealthComponent)
	{
		HealthComponent->ApplyDamage(Damage);
	}
}

void APlayerShip::HandlePlayerDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over"));

		
		ASpaceInvaderNormal* GameMode = Cast<ASpaceInvaderNormal>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		GameMode->GameOver();
	}
}
