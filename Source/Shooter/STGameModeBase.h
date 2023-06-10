// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/CoreTypes.h"
#include "STGameModeBase.generated.h"


class AAIController;

UCLASS()
class SHOOTER_API ASTGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASTGameModeBase();

	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	void Killed(AController* KillerController, AController* VictimController);

	FGameData GetGameData() const { return  GameData;}
	int32 GetCurrentRoundNum() const { return CurrentRound;}
	int32 GetRoundSecondsRemaining() const {return RoundCountDown;}

	void RespawnRequest(AController* Controller);
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData GameData;

private:
	int32 CurrentRound;
	int32 RoundCountDown;
	FTimerHandle GameRoundTimerHandle;

	void SpawnBots();
	void StartRound();
	void GameTimerUpdate();

	void ResetPlayers();
	void ResetOnePlayer(AController* Controller);

	void CreateTeamsInfo();
	FLinearColor DetermineColorByTeamID(int32 TeamID) const;
	void SetPlayerColor(AController* Controller);

	void LogPlayerInfo();

	void StartRespawn(AController* Controller);

	void GameOver();
};
