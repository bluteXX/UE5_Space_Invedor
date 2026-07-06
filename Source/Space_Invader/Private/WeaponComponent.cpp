#include "WeaponComponent.h"
#include "Projectile.h"
#include "Damageable.h"
#include "GameFramework/Actor.h"

// ==================== Lifecycle ====================

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	TimeSinceLastShot = FireCooldown;
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TimeSinceLastShot += DeltaTime;
}

// ==================== Gameplay Functions ====================

bool UWeaponComponent::TryFire()
{
	if (!IsReady() || !ProjectileClass) return false;

	AActor* Owner = GetOwner();
	if (!Owner) return false;

	FVector SpawnLocation;
	FRotator SpawnRotation;

	if (Muzzle)
	{
		SpawnLocation = Muzzle->GetComponentLocation();

		FVector ForwardDir = Muzzle->GetForwardVector();
		SpawnRotation = ForwardDir.Rotation();
	}
	else
	{
		SpawnLocation = Owner->GetActorLocation() + Owner->GetActorForwardVector() * 60.0f;
		SpawnRotation = Owner->GetActorRotation();
	}

	FTransform SpawnTransform(SpawnRotation, SpawnLocation);

	AProjectile* NewProjectile = GetWorld()->SpawnActorDeferred<AProjectile>(
		ProjectileClass, SpawnTransform, Owner);

	if (NewProjectile)
	{
		NewProjectile->bIsEnemyProjectile = bIsEnemyWeapon;

		if (Owner->Implements<UDamageable>())
		{
			NewProjectile->OwnerTeam = IDamageable::Execute_GetTeamID(Owner);
		}

		NewProjectile->FinishSpawning(SpawnTransform);
	}

	TimeSinceLastShot = 0.0f;
	return NewProjectile != nullptr;
}