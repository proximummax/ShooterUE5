// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/STBaseWeapon.h"
#include "Shooter/Public/CoreTypes.h"
#include "STWeaponComponent.generated.h"

class ASTBaseWeapon;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTER_API USTWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTWeaponComponent();

	void StartFire();
	void StopFire();
	void NextWeapon();
	void Reload();

	bool GetWeaponUIData(FWeaponUIData& UIData) const;
	bool GetAmmoData(FAmmoData& AmmoData) const;
protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category= "Weapon")
	TArray<FWeaponData> WeaponsDatas;
	UPROPERTY(EditDefaultsOnly, Category= "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";
	UPROPERTY(EditDefaultsOnly, Category= "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";
	UPROPERTY(EditDefaultsOnly, Category= "Animation")
	UAnimMontage* EquipAnimMontage;

private:
	UPROPERTY()
	ASTBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTBaseWeapon*> Weapons;

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;
	
	int32 CurrentWeaponIndex = 0;
	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;
	void SpawnWeapons();
	void AttachWeaponToSocket(ASTBaseWeapon* Weapon, USkeletalMeshComponent* CharacterMesh, const FName& SocketName);
	void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimations();
	
	void OnEquipFinished(USkeletalMeshComponent* SkeletalMeshComponent);
	void OnRealoadFinished(USkeletalMeshComponent* SkeletalMeshComponent);
	
	bool CanFire() const;
	bool CanEquip() const;
	bool CanReload() const;

	void OnEmptyClip();
	void ChangeClip();
};
