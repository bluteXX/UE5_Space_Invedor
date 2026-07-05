#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPACE_INVADER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	float CurrentHealth = 100.0f;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return CurrentHealth <= 0.0f; }

protected:
	virtual void BeginPlay() override;

private:
	bool bIsDead = false;
};