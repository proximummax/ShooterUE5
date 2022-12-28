// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ASTGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	virtual void BeginPlay() override;
private:
	void DrawCrossHair();
};
