// Shooter, All Rights Reserved


#include "Components/STAIPerceptionComponent.h"

#include <AIController.h>

#include "STUtils.h"
#include "Components/STHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USTAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);

	if (PercieveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (auto PercieveActor : PercieveActors)
	{
		const auto HealthComponent = STUtils::GetSTPlayerComponent<USTHealthComponent>(PercieveActor);

		const auto PercievePawn = Cast<APawn>(PercieveActor);
		bool AreEnemies = PercievePawn && STUtils::AreEnemies(Controller, PercievePawn->Controller);
		
		if (!HealthComponent || HealthComponent->IsDead() || !AreEnemies) continue;

		const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
		if (CurrentDistance >= BestDistance) continue;

		BestDistance = CurrentDistance;
		BestPawn = PercieveActor;
	}

	return BestPawn;
}
