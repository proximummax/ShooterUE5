// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STRespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API USTRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTRespawnComponent();

	void Respawn(int32 RespawnTime);

	int32 GetRespawnCountDown() const { return RespawnCountDown; }
	bool IsRespawnTimerInProgress() const;
private:
	FTimerHandle RespawnTimerHandle;
	int32 RespawnCountDown = 0;

	void RespawnTimerUpdate();
};
