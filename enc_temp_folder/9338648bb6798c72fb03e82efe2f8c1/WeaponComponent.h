#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class AProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPACE_INVADER_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();
	void SetMuzzle(USceneComponent* NewMuzzle) { Muzzle = NewMuzzle; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float FireCooldown = 0.5f;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bIsEnemyWeapon = false;


	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool TryFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool IsReady() const { return TimeSinceLastShot >= FireCooldown; }

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float TimeSinceLastShot = 0.0f;
	UPROPERTY()
	USceneComponent* Muzzle = nullptr;
};