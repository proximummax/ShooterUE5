// Shooter, All Rights Reserved


#include "Pickups/STHealthPickup.h"

#include "STUtils.h"
#include "Components/STHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickUp, All, All);

bool ASTHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STUtils::GetSTPlayerComponent<USTHealthComponent>(PlayerPawn);
	if(!HealthComponent || HealthComponent->IsDead())
		return false;

	return HealthComponent->TryToAddHealth(HealthAmount);
}
