// Shooter, All Rights Reserved


#include "AI/STAIController.h"
#include <BehaviorTree/BlackboardComponent.h>
#include "AI/STAICharacter.h"
#include "Components/STAIPerceptionComponent.h"
#include "Components/STRespawnComponent.h"

ASTAIController::ASTAIController()
{
	STPerceptionComponent = CreateDefaultSubobject<USTAIPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*STPerceptionComponent);

	STRespawnComponent = CreateDefaultSubobject<USTRespawnComponent>("RespawnComponent");

	
	bWantsPlayerState = true;
}

void ASTAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const auto AimActor = GetFocusOnActor();

	SetFocus(AimActor);
}

void ASTAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto CharacterAI = Cast<ASTAICharacter>(InPawn);
	if (!CharacterAI) return;

	RunBehaviorTree(CharacterAI->BehaviorTree);
}

AActor* ASTAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;

	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
