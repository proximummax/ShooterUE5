// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STWeaponFXComponent.generated.h"

class UNiagaraSystem;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API USTWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTWeaponFXComponent();

	void PlayImpactFX(const FHitResult &Hit);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="VFX")
	UNiagaraSystem* Effect;
};
