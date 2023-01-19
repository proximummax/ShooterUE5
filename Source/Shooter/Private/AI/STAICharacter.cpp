// Shooter, All Rights Reserved


#include "AI/STAICharacter.h"
#include "AI/STAIController.h"
#include "Components/STAIWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ASTAICharacter::ASTAICharacter(const FObjectInitializer& ObjInit):
Super(ObjInit.SetDefaultSubobjectClass<USTAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASTAIController::StaticClass();

	bUseControllerRotationYaw = false;
	const auto CharacterMovementComponent = GetCharacterMovement();

	if(!CharacterMovementComponent)
		return;
	
	CharacterMovementComponent->bUseControllerDesiredRotation = true;
	CharacterMovementComponent->RotationRate = FRotator(0.0f,200.0f,0.0f);
}

