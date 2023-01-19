// Shooter, All Rights Reserved


#include "AI/STFindEnemyService.h"

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>

#include "STUtils.h"
#include "Components/STAIPerceptionComponent.h"

USTFindEnemyService::USTFindEnemyService()
{
	NodeName = "Find Enemy";
}

void USTFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if(BlackBoard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = STUtils::GetSTPlayerComponent<USTAIPerceptionComponent>(Controller);
		if(PerceptionComponent)
		{
			BlackBoard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
