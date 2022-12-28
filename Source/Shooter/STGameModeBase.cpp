// Shooter, All Rights Reserved


#include "STGameModeBase.h"
#include "Player/STBaseCharacter.h"
#include "Player/STPlayerController.h"
#include "UI/STGameHUD.h"

ASTGameModeBase::ASTGameModeBase()
{
	DefaultPawnClass = ASTBaseCharacter::StaticClass();
	PlayerControllerClass = ASTPlayerController::StaticClass();
	HUDClass = ASTGameHUD::StaticClass();
}

