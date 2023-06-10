// Shooter, All Rights Reserved


#include "UI/STSpectatorWidget.h"

#include "STUtils.h"
#include "Components/STRespawnComponent.h"

bool  USTSpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
	const auto RespawnComponent = STUtils::GetSTPlayerComponent<USTRespawnComponent>(GetOwningPlayer());

	if(!RespawnComponent || !RespawnComponent->IsRespawnTimerInProgress()) return false;

	CountDownTime = RespawnComponent->GetRespawnCountDown();
	return true;
}
