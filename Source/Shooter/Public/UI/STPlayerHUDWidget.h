// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Shooter/Public/CoreTypes.h"
#include "CoreTypes.h"
#include "Components/STHealthComponent.h"
#include "Components/STWeaponComponent.h"
#include "STPlayerHUDWidget.generated.h"

UCLASS()
class SHOOTER_API USTPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	UFUNCTION(BlueprintCallable, Category="UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool GetWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool GetAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool IsPlayerSpectating() const;
	
	UFUNCTION(BlueprintImplementableEvent, Category="UI")
	void OnTakeDamage();

	
	virtual bool Initialize() override;
private:
	void OnHealthChanged(float Health, float HealthDelta);
	void OnNewPawn(APawn* Pawn);
};
