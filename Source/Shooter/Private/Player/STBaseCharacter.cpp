// Shooter, All Rights Reserved


#include "Player/STBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/STCharacterMovementComponent.h"
#include "Components/STHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/STWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"


DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

ASTBaseCharacter::ASTBaseCharacter(const FObjectInitializer& ObjInit)
:Super(ObjInit.SetDefaultSubobjectClass<USTCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USTHealthComponent>("HealthComponent");
	
	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
	HealthTextComponent->SetOwnerNoSee(true);
	
	WeaponComponent = CreateDefaultSubobject<USTWeaponComponent>("WeaponComponent");
	
}

void ASTBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());
	check(GetMesh());
	
	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &ASTBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this,&ASTBaseCharacter::OnGroundLanded);

}

void ASTBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASTBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ASTBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveBack", this, &ASTBaseCharacter::MoveBack);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveLeft", this, &ASTBaseCharacter::MoveLeft);

	PlayerInputComponent->BindAxis("LookUp", this, &ASTBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTBaseCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTBaseCharacter::Jump);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTBaseCharacter::OnStopRunning);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTWeaponComponent::StopFire);

	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTWeaponComponent::Reload);
}

bool ASTBaseCharacter::IsRunning() const
{
	return  WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float ASTBaseCharacter::GetMovementDirection() const
{
	if(GetVelocity().IsZero())
		return 0.0f;
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASTBaseCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTBaseCharacter::MoveBack(float Amount)
{
	if(Amount == 0.0f) return;
	AddMovementInput(GetActorForwardVector(), -Amount);
}

void ASTBaseCharacter::MoveRight(float Amount)
{
	if(Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASTBaseCharacter::MoveLeft(float Amount)
{
	if(Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), -Amount);
}

void ASTBaseCharacter::OnStartRunning()
{
	WantsToRun = true;
}

void ASTBaseCharacter::OnStopRunning()
{
	WantsToRun = false;
}
void ASTBaseCharacter::OnDeath()
{
//	PlayAnimMontage(DeathAnimMontage);

	GetCharacterMovement()-> DisableMovement();
	
	SetLifeSpan(5.0f);
	if(Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetSimulatePhysics(true);
}

void ASTBaseCharacter::OnHealthChanged(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"),Health)));
}

void ASTBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;

	if(FallVelocityZ < LandedDamageVelocity.X)
		return;
	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity,LandedDamage, FallVelocityZ);
	TakeDamage(FinalDamage, FDamageEvent {},nullptr, nullptr);
	
}





