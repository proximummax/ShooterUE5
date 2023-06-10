// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "Weapon/STBaseWeapon.h"
#include "STRifleWeapon.generated.h"

class USTWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	FString TraceTargetName = "TraceTarget";
	
	virtual void BeginPlay() override;
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
private:
	FTimerHandle ShotTimerHandle;

	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;

	void MakeDamage(const FHitResult& HitResult);
	void SetMuzzleFXVisibility(bool Visible);

	void InitMuzzleFX();
	void SpawnTraceFX(const FVector& TraceStart,const FVector& TraceEnd);

	AController* GetController() const;
};
