// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STPlayerController.generated.h"

class USTRespawnComponent;
UCLASS()
class SHOOTER_API ASTPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASTPlayerController();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
	USTRespawnComponent* STRespawnComponent;

	virtual void OnPossess(APawn* InPawn) override;
};
