// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "STEnemyEnvQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USTEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
	
public:

	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FName EnemyActorKeyName = "EnemyActor";
};
