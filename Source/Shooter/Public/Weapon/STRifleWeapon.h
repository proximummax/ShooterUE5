// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STBaseWeapon.h"
#include "STRifleWeapon.generated.h"

class USTWeaponFXComponent;
UCLASS()
class SHOOTER_API ASTRifleWeapon : public ASTBaseWeapon
{
	GENERATED_BODY()
public:
	ASTRifleWeapon();

	virtual void StartFire() override;
	virtual void StopFire() override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float TimeBetweenShots = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageAmount = 10.0f;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="VFX")
	USTWeaponFXComponent* WeaponFXComponent;

	virtual void BeginPlay() override;
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
private:
	FTimerHandle ShotTimerHandle;
	void MakeDamage(const FHitResult& HitResult);
};
