// Shooter, All Rights Reserved


#include "AI/Decorators/STNeedAmmopDecorator.h"
#include "AIController.h"
#include "STUtils.h"
#include "Components/STAIWeaponComponent.h"

USTNeedAmmopDecorator::USTNeedAmmopDecorator()
{
	NodeName = "Need Ammo";
}

bool USTNeedAmmopDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller)
		return false;

	const auto WeaponComponent = STUtils::GetSTPlayerComponent<USTWeaponComponent>(Controller->GetPawn());

	if (!WeaponComponent)
		return false;

	return WeaponComponent->NeedAmmo(WeaponClass);

	return false;
}
