// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Shooter/Public/CoreTypes.h"
#include "STHealthComponent.generated.h"

class UCameraShakeBase;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTER_API USTHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTHealthComponent();
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category= "Health")
	bool IsDead() const { return FMath::IsNearlyZero(Health); };

	UFUNCTION(BlueprintCallable, Category= "Health")
	float GetHealthPercent() const { return Health / MaxHealth; }

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;
	bool TryToAddHealth(float HealthToAdd);
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta=(ClampMin = "0.0", ClampMax = "100.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Heal")
	bool AutoHeal = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Heal", meta = (EditCondition = "AutoHeal"))
	float UpdateTime = 0.3f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Heal", meta = (EditCondition = "AutoHeal"))
	float HealDelay = 3.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Heal", meta = (EditCondition = "AutoHeal"))
	float HealModifier = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "VFX", meta = (EditCondition = "AutoHeal"))
	TSubclassOf<UCameraShakeBase> CameraShake;
	virtual void BeginPlay() override;
private:
	float Health = 0.0f;
	FTimerHandle HealTimerHandle;
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	                     AController* InstigatedBy, AActor* DamageCauser);

	void Heal();
	void SetHealth(float NewHealth);

	void PlayCameraShake();
};
