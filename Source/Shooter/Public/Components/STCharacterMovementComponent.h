// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STCharacterMovementComponent.generated.h"
/**
 * 
 */
UCLASS()
class SHOOTER_API USTCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement", meta = (ClampMin ="1.5", ClampMax = "3.0"))
	float RunModifer = 2.0f;
	
	virtual  float GetMaxSpeed() const override;
};
