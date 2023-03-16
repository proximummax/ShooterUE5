// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "..\..\..\Public\Weapon\STBaseWeapon.h"
#include "STNeedAmmopDecorator.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USTNeedAmmopDecorator : public UBTDecorator
{
	GENERATED_BODY()

	USTNeedAmmopDecorator();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<ASTBaseWeapon> WeaponClass;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
