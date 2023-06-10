// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/STHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "STBaseCharacter.generated.h"



class USTHealthComponent;
class USTWeaponComponent;
UCLASS()
class SHOOTER_API ASTBaseCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	ASTBaseCharacter(const FObjectInitializer& ObjInit);
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
	USTHealthComponent* HealthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
	USTWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere)
	float RunSpeed = 900.0f;

	UPROPERTY(EditDefaultsOnly, Category= "Animation")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category= "Damage")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);
	UPROPERTY(EditDefaultsOnly, Category= "Damage")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	UPROPERTY(EditDefaultsOnly, Category= "Material")
	FName MaterialColorName = "Paint Color";
	
	float DefaultSpeed = 600.0f;
	virtual void BeginPlay() override;
	virtual void OnDeath();
public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category= "Movement")
	float GetMovementDirection() const;

	void SetPlayerColor(const FLinearColor& Color);
private:

	void OnHealthChanged(float Health, float HealthDelta);
	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);

};
