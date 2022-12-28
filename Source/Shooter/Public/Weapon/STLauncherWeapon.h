// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "STProjectile.h"
#include "Weapon/STBaseWeapon.h"
#include "STLauncherWeapon.generated.h"

class ASTProjectile;

UCLASS()
class SHOOTER_API ASTLauncherWeapon : public ASTBaseWeapon
{
	GENERATED_BODY()
public:
	virtual void StartFire() override;

	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	TSubclassOf<ASTProjectile> ProjectileClass;
	
	virtual void MakeShot() override;
	
};
