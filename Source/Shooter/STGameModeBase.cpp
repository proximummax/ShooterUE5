// Shooter, All Rights Reserved


#include "STGameModeBase.h"

#include "AIController.h"
#include "STUtils.h"
#include "Components/STRespawnComponent.h"
#include "Player/STBaseCharacter.h"
#include "Player/STPlayerController.h"
#include "Player/STPlayerState.h"
#include "UI/STGameHUD.h"
#include <Runtime/Engine/Public/EngineUtils.h>

ASTGameModeBase::ASTGameModeBase()
{
	DefaultPawnClass = ASTBaseCharacter::StaticClass();
	PlayerControllerClass = ASTPlayerController::StaticClass();
	HUDClass = ASTGameHUD::StaticClass();
	PlayerStateClass = ASTPlayerState::StaticClass();
}

void ASTGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	CreateTeamsInfo();

	CurrentRound = 1;
	StartRound();
}

UClass* ASTGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
		return AIPawnClass;

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
	const auto KillerPlayerState = Cast<ASTPlayerState>(KillerController->PlayerState);
	if (!KillerPlayerState) return;

	const auto VictimPlayerState = Cast<ASTPlayerState>(VictimController->PlayerState);
	if (!VictimPlayerState) return;

	KillerPlayerState->AddKill();
	VictimPlayerState->AddDeath();

	StartRespawn(VictimController);
}

void ASTGameModeBase::SpawnBots()
{
	if (!GetWorld()) return;

	for (int32 i = 0; i < GameData.PlayersNum - 1; i++)
	{
		FActorSpawnParameters SpawnParameters;

		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnParameters);
		RestartPlayer(AIController);
	}
}

void ASTGameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ThisClass::GameTimerUpdate, 1.0f, true);
}

void ASTGameModeBase::GameTimerUpdate()
{
	RoundCountDown--;
	if (RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			GameOver();
		}
	}
}

void ASTGameModeBase::ResetPlayers()
{
	if (!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void ASTGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void ASTGameModeBase::CreateTeamsInfo()
{
	if (!GetWorld()) return;

	int32 TeamID = 1;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller)
			continue;

		const auto PlayerState = Cast<ASTPlayerState>(Controller->PlayerState);
		if (!PlayerState)
			continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		SetPlayerColor(Controller);

		TeamID = TeamID == 1 ? 2 : 1;
	}
}

FLinearColor ASTGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
	if (TeamID - 1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID - 1];
	}

	return GameData.DefaultTeamColor;
}

void ASTGameModeBase::SetPlayerColor(AController* Controller)
{
	if (!Controller) return;

	const auto Character = Cast<ASTBaseCharacter>(Controller->GetPawn());
	if (!Character) return;

	const auto PlayerState = Cast<ASTPlayerState>(Controller->PlayerState);
	if (!PlayerState) return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ASTGameModeBase::LogPlayerInfo()
{
}

void ASTGameModeBase::StartRespawn(AController* Controller)
{
	const auto RespawnComponent = STUtils::GetSTPlayerComponent<USTRespawnComponent>(Controller);
	if(!RespawnComponent) return;

	RespawnComponent->Respawn(GameData.RespawnTime);
}
void ASTGameModeBase::RespawnRequest(AController* Controller)
{
	ResetOnePlayer(Controller);
}

void ASTGameModeBase::GameOver()
{
	for(auto Pawn: TActorRange<APawn>(GetWorld()))
	{
		if(Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}
}