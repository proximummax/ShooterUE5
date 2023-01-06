// Shooter, All Rights Reserved


#include "Weapon/Components/STWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"

USTWeaponFXComponent::USTWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USTWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}


