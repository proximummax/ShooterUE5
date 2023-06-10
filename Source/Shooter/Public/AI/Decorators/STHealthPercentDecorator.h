// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STHealthPercentDecorator.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USTHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()


	USTHealthPercentDecorator();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float HealthPercent = 0.6f;
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
