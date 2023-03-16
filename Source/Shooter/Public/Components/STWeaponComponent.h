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

	virtual void StartFire();
	void StopFire();
	virtual void NextWeapon();
	void Reload();

	bool GetWeaponUIData(FWeaponUIData& UIData) const;
	bool GetAmmoData(FAmmoData& AmmoData) const;
	bool TryToAddAmmo(TSubclassOf<ASTBaseWeapon> WeaponType, int32 ClipsAmount);
	bool NeedAmmo(TSubclassOf<ASTBaseWeapon> WeaponType);
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

	UPROPERTY()
	ASTBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTBaseWeapon*> Weapons;
		
	bool CanFire() const;
	bool CanEquip() const;
	void EquipWeapon(int32 WeaponIndex);

	int32 CurrentWeaponIndex = 0;
private:
	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;
	
	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;
	void SpawnWeapons();
	void AttachWeaponToSocket(ASTBaseWeapon* Weapon, USkeletalMeshComponent* CharacterMesh, const FName& SocketName);


	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimations();
	
	void OnEquipFinished(USkeletalMeshComponent* SkeletalMeshComponent);
	void OnRealoadFinished(USkeletalMeshComponent* SkeletalMeshComponent);

	bool CanReload() const;

	void OnEmptyClip(ASTBaseWeapon* AmmoEmpty);
	void ChangeClip();
};
