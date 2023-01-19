// Shooter, All Rights Reserved


#include "Weapon/STLauncherWeapon.h"
#include "Weapon/STProjectile.h"

void ASTLauncherWeapon::StartFire()
{
	MakeShot();
}

void ASTLauncherWeapon::MakeShot()
{
	if (!GetWorld())
		return;
	if(IsAmmoEmpty())
		return;
	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
		return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	ASTProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASTProjectile>(ProjectileClass, SpawnTransform);
	if (Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}
	DecreaseAmmo();

	SpawnMuzzleFX();
}
