// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Shooter/Public/CoreTypes.h"
#include "STWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API USTWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTWeaponFXComponent();

	void PlayImpactFX(const FHitResult &Hit);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="VFX")
	FImpactData DefaultImpactData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="VFX")
	TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;
};
