// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STPlayerState.generated.h"


UCLASS()
class SHOOTER_API ASTPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	int32 GetTeamID() { return TeamID; }
	void SetTeamID(int32 ID) { TeamID = ID; }

	void SetTeamColor(FLinearColor Color) { TeamColor = Color; }
	FLinearColor GetTeamColor() { return TeamColor; }

	void AddKill() { KillsNum++; }
	void AddDeath() { DeathNum++; }

	int32 GetKillsNum(){ return KillsNum; }
	int32 GetDeathNum(){ return DeathNum; }
	void LogInfo();
private:
	int32 TeamID;
	FLinearColor TeamColor;

	int32 KillsNum = 0;
	int32 DeathNum = 0;
};
