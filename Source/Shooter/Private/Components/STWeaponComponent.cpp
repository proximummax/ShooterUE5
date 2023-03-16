// Shooter, All Rights Reserved


#include "Components/STWeaponComponent.h"

#include "Animations/STEquipFinishedAnimNotify.h"
#include "Animations/STReloadFinishedAnimNotify.h"
#include "Weapon/STBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/AnimUtils.h"

constexpr static int32 WeaponNum = 2;
USTWeaponComponent::USTWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(WeaponsDatas.Num() == WeaponNum, TEXT("Our character can hold only %i weapons"), WeaponNum);
	
	InitAnimations();
	CurrentWeaponIndex = 0;
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void USTWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
}

void USTWeaponComponent::SpawnWeapons()
{
	if (!GetWorld()) return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	for (auto WeaponData : WeaponsDatas)
	{
		auto Weapon = GetWorld()->SpawnActor<ASTBaseWeapon>(WeaponData.WeaponClass);
		if (!Weapon) continue;

		Weapon->OnClipEmpty.AddUObject(this, &USTWeaponComponent::OnEmptyClip);

		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
}

void USTWeaponComponent::AttachWeaponToSocket(ASTBaseWeapon* Weapon, USkeletalMeshComponent* CharacterMesh,
                                              const FName& SocketName)
{
	if (!Weapon || !CharacterMesh) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(CharacterMesh, AttachmentRules, SocketName);
}

void USTWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num()) return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	const auto CurrentWeaponData = WeaponsDatas.FindByPredicate([&](const FWeaponData& Data)
	{
		return Data.WeaponClass == CurrentWeapon->GetClass();
	});

	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);

	EquipAnimInProgress = true;
	PlayAnimMontage(EquipAnimMontage);
}


void USTWeaponComponent::StartFire()
{
	if (!CanFire()) return;
	CurrentWeapon->StartFire();
}

void USTWeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void USTWeaponComponent::NextWeapon()
{
	if (!CanEquip())
		return;

	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % WeaponsDatas.Num();
	EquipWeapon(CurrentWeaponIndex);
}


void USTWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(Animation);
}

void USTWeaponComponent::InitAnimations()
{
	auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<USTEquipFinishedAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &USTWeaponComponent::OnEquipFinished);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Equip anim notify is forgotten to set"));
	}

	for (auto WeaponData : WeaponsDatas)
	{
		auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USTReloadFinishedAnimNotify>(WeaponData.ReloadAnimMontage);
		if (!ReloadFinishedNotify)
		{
			UE_LOG(LogTemp, Error, TEXT("Reload anim notify is forgotten to set"));
		}

		ReloadFinishedNotify->OnNotified.AddUObject(this, &USTWeaponComponent::OnRealoadFinished);
	}
}

void USTWeaponComponent::OnEquipFinished(USkeletalMeshComponent* SkeletalMeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (Character->GetMesh() != SkeletalMeshComponent) return;
	EquipAnimInProgress = false;
}

void USTWeaponComponent::OnRealoadFinished(USkeletalMeshComponent* SkeletalMeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (Character->GetMesh() != SkeletalMeshComponent) return;
	ReloadAnimInProgress = false;
}


bool USTWeaponComponent::CanFire() const
{
	return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool USTWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress && !ReloadAnimInProgress;
}

void USTWeaponComponent::Reload()
{
	ChangeClip();
}

bool  USTWeaponComponent::GetWeaponUIData(FWeaponUIData& UIData) const
{
	if (!CurrentWeapon)
		return false;

	UIData = CurrentWeapon->GetUIData();
	return true;
}

bool USTWeaponComponent::GetAmmoData(FAmmoData& AmmoData) const
{
	if(!CurrentWeapon)
		return  false;

	AmmoData = CurrentWeapon->GetAmmoData();
	return  true;
}

bool USTWeaponComponent::TryToAddAmmo(TSubclassOf<ASTBaseWeapon> WeaponType, int32 ClipsAmount)
{
	for (auto Weapon : Weapons)
	{
		if(!Weapon || !Weapon->IsA(WeaponType))
			continue;

		return Weapon->TryToAddAmmo(ClipsAmount);
	}
	return  false;
}

bool USTWeaponComponent::NeedAmmo(TSubclassOf<ASTBaseWeapon> WeaponType)
{

	for (auto Weapon : Weapons)
	{
		if (!Weapon || !Weapon->IsA(WeaponType))
			continue;

		return Weapon->IsAmmoFull();
	}
	return  false;

	return false;
}

bool USTWeaponComponent::CanReload() const
{
	return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress && CurrentWeapon->CanReload();
}

void USTWeaponComponent::OnEmptyClip(ASTBaseWeapon* AmmoEmpty)
{
	if(!AmmoEmpty)
		return;
	
	if(CurrentWeapon == AmmoEmpty)
		ChangeClip();
	else
	{
		for (auto Weapon : Weapons)
		{
			if(Weapon != AmmoEmpty)
				continue;
			Weapon->ChangeClip();
			break;
		}
	}
}

void USTWeaponComponent::ChangeClip()
{
	if (!CanReload()) return;
	
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	ReloadAnimInProgress = true;
	PlayAnimMontage(CurrentReloadAnimMontage);
}
