// Shooter, All Rights Reserved


#include "Player/STBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
//#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/STCharacterMovementComponent.h"

ASTBaseCharacter::ASTBaseCharacter(const FObjectInitializer& ObjInit)
:Super(ObjInit.SetDefaultSubobjectClass<USTCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ASTBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASTBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASTBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASTBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveBack", this, &ASTBaseCharacter::MoveBack);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveLeft", this, &ASTBaseCharacter::MoveLeft);

	PlayerInputComponent->BindAxis("LookUp", this, &ASTBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTBaseCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTBaseCharacter::Jump);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTBaseCharacter::OnStopRunning);
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

