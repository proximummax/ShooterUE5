// Shooter, All Rights Reserved

#include "AI/STChangeWeaponService.h"
#include "STUtils.h"
#include "AIController.h"
#include "Components/STWeaponComponent.h"

USTChangeWeaponService::USTChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void USTChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();

	if (Controller)
	{
		const auto WeaponComponent = STUtils::GetSTPlayerComponent<USTWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}
	}


	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
