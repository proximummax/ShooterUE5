// Shooter, All Rights Reserved


#include "AI/STNextLocationTask.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

USTNextLocationTask::USTNextLocationTask()
{
	NodeName = "Next Location";
}

EBTNodeResult::Type USTNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if(!Controller || ! BlackBoard) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return  EBTNodeResult::Failed;

	const auto NavSystem = UNavigationSystemV1::GetCurrent(Pawn);
	if(!NavSystem) return  EBTNodeResult::Failed;

	FNavLocation NavResult;
	auto Location = Pawn ->GetActorLocation();
	if(!SelfCenter)
	{
		auto CenterActor = Cast<AActor>(BlackBoard->GetValueAsObject(CenterActorKey.SelectedKeyName));
		if(!CenterActor) return  EBTNodeResult::Failed;
		Location = CenterActor->GetActorLocation();
	}
	
	const auto Found = NavSystem->GetRandomReachablePointInRadius(Location,Radius, NavResult);
	if(!Found) return EBTNodeResult::Failed;

	BlackBoard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavResult.Location);

	return  EBTNodeResult::Succeeded;

}
