// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/STBaseCharacter.h"
#include "STPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
UCLASS()
class SHOOTER_API ASTPlayerCharacter : public ASTBaseCharacter
{
	GENERATED_BODY()
public:
	ASTPlayerCharacter(const FObjectInitializer& ObjInit);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	virtual void OnDeath() override;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;

private:
	bool WantsToRun = false;
	bool IsMovingForward = false;

	void MoveForward(float Amount);
	void MoveBack(float Amount);
	void MoveRight(float Amount);
	void MoveLeft(float Amount);

	void OnStartRunning();
	void OnStopRunning();
};
