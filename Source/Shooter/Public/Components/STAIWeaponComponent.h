// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/STWeaponComponent.h"
#include "STAIWeaponComponent.generated.h"

UCLASS()
class SHOOTER_API USTAIWeaponComponent : public USTWeaponComponent
{
	GENERATED_BODY()
public:
	virtual void StartFire() override;
	virtual void NextWeapon() override;
};
