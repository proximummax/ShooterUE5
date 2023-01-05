// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STBasePickup.h"
#include "STHealthPickup.generated.h"

UCLASS()
class SHOOTER_API ASTHealthPickup : public ASTBasePickup
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup", meta=(ClampMin="1.0", ClampMax="10.0"))
	float HealthAmount = 10.0f;
private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
