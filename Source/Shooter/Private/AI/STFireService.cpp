// Shooter, All Rights Reserved


#include "AI/STFireService.h"

#include "AIController.h"
#include "STUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STWeaponComponent.h"

USTFireService::USTFireService()
{
	NodeName = "Fire";
}

void USTFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	const auto Controller = OwnerComp.GetAIOwner();

	bool HasAim = BlackBoard && BlackBoard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if(Controller)
	{
		const auto WeaponComponent = STUtils::GetSTPlayerComponent<USTWeaponComponent>(Controller->GetPawn());
		if(WeaponComponent)
		{
			HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
			
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
