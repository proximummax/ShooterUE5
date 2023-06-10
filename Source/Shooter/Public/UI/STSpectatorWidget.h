// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STSpectatorWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USTSpectatorWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category= "UI")
	bool GetRespawnTime(int32& CountDownTime) const;
};
