// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STGameDataWidget.generated.h"

class ASTGameModeBase;
class ASTPlayerState;

UCLASS()
class SHOOTER_API USTGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category= "UI")
	int32 GetKillsNum() const;

	UFUNCTION(BlueprintCallable, Category= "UI")
	int32 GetCurrentRoundNum() const;

	UFUNCTION(BlueprintCallable, Category= "UI")
	int32 GetTotalRoundsNum() const;

	UFUNCTION(BlueprintCallable, Category= "UI")
	int32 GetRoundSecondsRemaining() const;

private:
	ASTGameModeBase* GetSTGameMode() const;

	ASTPlayerState* GetSTPlayerState() const;
};
