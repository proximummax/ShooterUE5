// Shooter, All Rights Reserved

#include "Components/STRespawnComponent.h"
#include "Player/STPlayerController.h"

ASTPlayerController::ASTPlayerController()
{
	STRespawnComponent = CreateDefaultSubobject<USTRespawnComponent>("RespawnComponent");

}

void ASTPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OnNewPawn.Broadcast(InPawn);
}