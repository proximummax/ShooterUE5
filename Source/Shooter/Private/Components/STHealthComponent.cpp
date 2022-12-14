// Shooter, All Rights Reserved


#include "Components/STHealthComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

USTHealthComponent::USTHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool USTHealthComponent::TryToAddHealth(float HealthToAdd)
{
	if (Health >= MaxHealth)
		return false;
	Health = FMath::Clamp(Health + HealthToAdd, 0, MaxHealth);
	return true;
}

void USTHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTHealthComponent::OnTakeAnyDamage);
	}
}

void USTHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                         AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld())
		return;
	SetHealth(Health - Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (AutoHeal && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTHealthComponent::Heal, UpdateTime, true,
		                                       HealDelay);
	}
	PlayCameraShake();
}

void USTHealthComponent::Heal()
{
	SetHealth(Health + HealModifier);

	if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void USTHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}

void USTHealthComponent::PlayCameraShake()
{
	if (IsDead()) return;

	const auto Player = Cast<APawn>(GetOwner());
	if(!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if(!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
	
}
