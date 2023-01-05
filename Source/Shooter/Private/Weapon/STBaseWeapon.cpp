// Shooter, All Rights Reserved


#include "Weapon/STBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)

ASTBaseWeapon::ASTBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMeshComponent);
}

void ASTBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	checkf(DefaultAmmo.Bullets > 0, TEXT("BUllets count couldn`t be less of equal zero"));
	checkf(DefaultAmmo.Clips > 0 , TEXT("Clips count couldn`t be less of equal zero"))
	check(WeaponMeshComponent);
	CurrentAmmo = DefaultAmmo;
}



void ASTBaseWeapon::MakeShot()
{
	
}

void ASTBaseWeapon::StartFire()
{
	
}
void ASTBaseWeapon::StopFire()
{
	
}

APlayerController* ASTBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player)
		return nullptr;

	return Player->GetController<APlayerController>();
}

bool ASTBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const APlayerController* Controller = GetPlayerController();
	if (!Controller)
		return false;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}

FVector ASTBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMeshComponent->GetSocketLocation(MuzzleSocketName);
}

bool ASTBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
		return false;

	TraceStart = ViewLocation;

	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * FVector(TraceMaxDistance);

	return true;
}
void ASTBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if(!GetWorld())
		return;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,
										 CollisionQueryParams);
}

void ASTBaseWeapon::DecreaseAmmo()
{
	if(CurrentAmmo.Bullets == 0) return;
	
	CurrentAmmo.Bullets--;
	LogAmmo();

	if(IsClipEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast(this);
	}
	
}
bool ASTBaseWeapon::IsAmmoEmpty() const
{
	return  !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}
bool ASTBaseWeapon::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

bool ASTBaseWeapon::IsAmmoFull() const
{
	return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

void ASTBaseWeapon::ChangeClip()
{
	if(CurrentAmmo.Infinite) return;
	if(CurrentAmmo.Clips == 0) return;
	
	CurrentAmmo.Clips--;
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
}

bool ASTBaseWeapon::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

bool ASTBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
	if(IsAmmoFull() || CurrentAmmo.Infinite || ClipsAmount <= 0)
		return false;
	if(IsAmmoEmpty())
	{
		UE_LOG(LogBaseWeapon, Display, TEXT("Ammo was empty"));
		CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips + ClipsAmount, 0, DefaultAmmo.Clips + 1);
		OnClipEmpty.Broadcast(this);
	}
	else if(CurrentAmmo.Clips < DefaultAmmo.Clips)
	{
		const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
		if(DefaultAmmo.Clips - NextClipsAmount >= 0)
		{
			UE_LOG(LogBaseWeapon, Display, TEXT("Clips were added"));
			CurrentAmmo.Clips = NextClipsAmount;
		}
		else
		{
			UE_LOG(LogBaseWeapon, Display, TEXT("Ammo is full now"));
			CurrentAmmo.Clips = DefaultAmmo.Clips;
			CurrentAmmo.Bullets = DefaultAmmo.Bullets;
		}
	}
	else
	{
		UE_LOG(LogBaseWeapon, Display, TEXT("Bullets were added"));
		CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	}
	return true;
}

void ASTBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}
