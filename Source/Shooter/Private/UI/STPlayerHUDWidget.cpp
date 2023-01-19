// Shooter, All Rights Reserved


#include "UI/STPlayerHUDWidget.h"

#include "Components/STHealthComponent.h"
#include "Components/STWeaponComponent.h"
#include "Shooter/Public/STUtils.h"

float USTPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = STUtils::GetSTPlayerComponent<USTHealthComponent>(GetOwningPlayerPawn());
	if(!HealthComponent)
		return 0.0f;
	
	return HealthComponent->GetHealthPercent();
}

bool USTPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent =  STUtils::GetSTPlayerComponent<USTWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent)
		return false;

	return WeaponComponent->GetWeaponUIData(UIData);
}

bool USTPlayerHUDWidget::GetAmmoData(FAmmoData& AmmoData) const
{

	const auto WeaponComponent = STUtils::GetSTPlayerComponent<USTWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent)
		return false;
	return WeaponComponent->GetAmmoData(AmmoData);
}

bool USTPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = STUtils::GetSTPlayerComponent<USTHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool USTPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

bool USTPlayerHUDWidget::Initialize()
{
	const auto HealthComponent = STUtils::GetSTPlayerComponent<USTHealthComponent>(GetOwningPlayerPawn());
	if(HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &USTPlayerHUDWidget::OnHealthChanged);
	}
	return Super::Initialize();
}

void USTPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if(HealthDelta < 0.0f)
	{
		OnTakeDamage();
	}

}

