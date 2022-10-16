// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "STBaseCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
UCLASS()
class SHOOTER_API ASTBaseCharacter : public  ACharacter
{
	GENERATED_BODY()
public:
	ASTBaseCharacter(const FObjectInitializer& ObjInit);
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
	USpringArmComponent *SpringArmComponent;
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
	UCameraComponent *CameraComponent;
	

	UPROPERTY(VisibleAnywhere)
	float RunSpeed = 900.0f;

	float DefaultSpeed = 600.0f;
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category= "Movement")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category= "Movement")
	float GetMovementDirection() const;
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
