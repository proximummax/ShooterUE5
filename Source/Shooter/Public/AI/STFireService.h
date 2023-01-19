// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STFireService.generated.h"

UCLASS()
class SHOOTER_API USTFireService : public UBTService
{
	GENERATED_BODY()
public:
	USTFireService();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
