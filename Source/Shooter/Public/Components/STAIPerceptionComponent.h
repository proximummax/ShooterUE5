// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Chaos/ChaosDebugDraw.h"
#include "Perception/AIPerceptionComponent.h"
#include "STAIPerceptionComponent.generated.h"


UCLASS()
class SHOOTER_API USTAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
public:
	AActor* GetClosestEnemy() const;
};
