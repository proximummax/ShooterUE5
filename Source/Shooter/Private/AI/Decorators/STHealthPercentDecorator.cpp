// Shooter, All Rights Reserved


#include "AI/Decorators/STHealthPercentDecorator.h"
#include "..\..\..\Public\AI\Decorators\STHealthPercentDecorator.h"
#include "AIController.h"
#include "STUtils.h"
#include "Components/STHealthComponent.h"

USTHealthPercentDecorator::USTHealthPercentDecorator()
{
	NodeName = "Health Percent";
}

bool USTHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{

	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller)
		return false;

	const auto HealthComponent = STUtils::GetSTPlayerComponent<USTHealthComponent>(Controller->GetPawn());
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->GetHealthPercent() <= HealthPercent;

}
