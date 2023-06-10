// Shooter, All Rights Reserved


#include "Components/STCharacterMovementComponent.h"
#include "Player/STPlayerCharacter.h"

float USTCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ASTPlayerCharacter* Player = Cast<ASTPlayerCharacter>(GetPawnOwner());

	return Player && Player->IsRunning() ? MaxSpeed * RunModifer : MaxSpeed;
}
