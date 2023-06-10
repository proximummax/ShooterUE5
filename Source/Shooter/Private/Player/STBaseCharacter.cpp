// Shooter, All Rights Reserved


#include "Player/STBaseCharacter.h"
#include "Components/STCharacterMovementComponent.h"
#include "Components/STHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/STWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"


DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

ASTBaseCharacter::ASTBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USTCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<USTHealthComponent>("HealthComponent");

	WeaponComponent = CreateDefaultSubobject<USTWeaponComponent>("WeaponComponent");
}

void ASTBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent);
	check(GetCharacterMovement());
	check(GetMesh());

	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &ASTBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &ASTBaseCharacter::OnGroundLanded);
}

void ASTBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}



float ASTBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero())
		return 0.0f;
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASTBaseCharacter::SetPlayerColor(const FLinearColor& Color)
{
	const auto MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (!MaterialInstance) return;

	MaterialInstance->SetVectorParameterValue(MaterialColorName, Color);
	UE_LOG(LogTemp, Warning, TEXT("COLOR iS SET"));
}


void ASTBaseCharacter::OnDeath()
{
	//	PlayAnimMontage(DeathAnimMontage);

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.0f);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetSimulatePhysics(true);
}

void ASTBaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{

}

void ASTBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;

	if (FallVelocityZ < LandedDamageVelocity.X)
		return;
	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}
