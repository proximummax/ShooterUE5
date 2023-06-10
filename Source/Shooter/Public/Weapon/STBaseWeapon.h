// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shooter/Public/CoreTypes.h"
#include "STBaseWeapon.generated.h"

class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class SHOOTER_API ASTBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	ASTBaseWeapon();

	FOnClipEmptySignature OnClipEmpty;
	
	virtual void StartFire();
	virtual void StopFire();

	void ChangeClip();
	bool CanReload() const;
	bool IsAmmoEmpty() const;
	bool IsAmmoFull() const;

	FWeaponUIData GetUIData() const {return  UIData;}
	FAmmoData GetAmmoData() const {return CurrentAmmo;}
	bool TryToAddAmmo(int32 ClipsAmount);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
	USkeletalMeshComponent* WeaponMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category= "Weapon")
	FName MuzzleSocketName = "MuzzleFlashSocket";
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category= "Weapon")
	float TraceMaxDistance = 1000.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category= "Weapon")
	FAmmoData DefaultAmmo{15, 10, false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	FWeaponUIData UIData;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	UNiagaraSystem* MuzzleFX;
	
	virtual void BeginPlay() override;
	
	virtual void MakeShot();
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	void DecreaseAmmo();
	bool IsClipEmpty() const;
	

	UNiagaraComponent* SpawnMuzzleFX();
	void LogAmmo();
private:
	FAmmoData CurrentAmmo;

	
};
