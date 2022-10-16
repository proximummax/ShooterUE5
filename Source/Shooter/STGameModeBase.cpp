// Shooter, All Rights Reserved


#include "STGameModeBase.h"
#include "Player/STBaseCharacter.h"
#include "Player/STPlayerController.h"

ASTGameModeBase::ASTGameModeBase()
{
	DefaultPawnClass = ASTBaseCharacter::StaticClass();
	PlayerControllerClass = ASTPlayerController::StaticClass();
}

