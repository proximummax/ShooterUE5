// Shooter, All Rights Reserved

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/STWeaponComponent.h"
#include "Player/STPlayerCharacter.h"

ASTPlayerCharacter::ASTPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

}

void ASTPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveBack", this, &ASTPlayerCharacter::MoveBack);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveLeft", this, &ASTPlayerCharacter::MoveLeft);

	PlayerInputComponent->BindAxis("LookUp", this, &ASTPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTPlayerCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTPlayerCharacter::Jump);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTPlayerCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTPlayerCharacter::OnStopRunning);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTWeaponComponent::StopFire);

	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTWeaponComponent::Reload);
}

void ASTPlayerCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTPlayerCharacter::MoveBack(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorForwardVector(), -Amount);
}

void ASTPlayerCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASTPlayerCharacter::MoveLeft(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), -Amount);
}

void ASTPlayerCharacter::OnStartRunning()
{
	WantsToRun = true;
}

void ASTPlayerCharacter::OnStopRunning()
{
	WantsToRun = false;
}

bool ASTPlayerCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

void ASTPlayerCharacter::OnDeath()
{
	Super::OnDeath();

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}
