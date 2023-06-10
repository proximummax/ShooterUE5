// Shooter, All Rights Reserved


#include "UI/STGameDataWidget.h"

#include "Player/STPlayerState.h"
#include "Shooter/STGameModeBase.h"

int USTGameDataWidget::GetKillsNum() const
{
	const auto PlayerState = GetSTPlayerState();
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}
int USTGameDataWidget::GetCurrentRoundNum()  const
{
	const auto GameMode = GetSTGameMode();
	return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}
int USTGameDataWidget::GetTotalRoundsNum() const
{
	const auto GameMode = GetSTGameMode();
	return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}
int USTGameDataWidget::GetRoundSecondsRemaining() const
{
	const auto GameMode = GetSTGameMode();
	return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

ASTGameModeBase* USTGameDataWidget::GetSTGameMode() const
{
	return GetWorld() ? Cast<ASTGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASTPlayerState* USTGameDataWidget::GetSTPlayerState() const
{
	return GetOwningPlayer() ? Cast<ASTPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}