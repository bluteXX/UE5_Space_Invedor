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

	// ==================== Lifecycle ====================

	UHealthComponent();

	// ==================== Gameplay Functions ====================

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(float Damage);

	// ==================== Delegates / Events ====================

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;

	// ==================== Configuration ====================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;

	// ==================== Runtime State ====================

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	float CurrentHealth = 100.0f;

protected:

	virtual void BeginPlay() override;

private:

	bool bIsDead = false;
};