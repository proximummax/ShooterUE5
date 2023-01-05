// Shooter, All Rights Reserved


#include "Pickups/STAmmoPickup.h"

#include "STUtils.h"
#include "Components/STHealthComponent.h"
#include "Components/STWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickUp, All, All);
bool ASTAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STUtils::GetSTPlayerComponent<USTHealthComponent>(PlayerPawn);
	if(!HealthComponent || HealthComponent->IsDead())
		return false;

	const auto WeaponComponent = STUtils::GetSTPlayerComponent<USTWeaponComponent>(PlayerPawn);
	if(!WeaponComponent)
		return false;
	
	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);

}
