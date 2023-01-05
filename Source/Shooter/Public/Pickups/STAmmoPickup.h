// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STBasePickup.h"
#include "Weapon/STBaseWeapon.h"
#include "STAmmoPickup.generated.h"

class ASTBaseWeapon;
UCLASS()
class SHOOTER_API ASTAmmoPickup : public ASTBasePickup
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup", meta=(ClampMin="1.0", ClampMax="10.0"))
	int32 ClipsAmount = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
	TSubclassOf<ASTBaseWeapon> WeaponType;
private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
