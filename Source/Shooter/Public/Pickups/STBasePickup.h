// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "STBasePickup.generated.h"

class USphereComponent;
UCLASS()
class SHOOTER_API ASTBasePickup : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Pickup")
	USphereComponent* CollisionComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Pickup")
	float RespawnTime = 5.0f;
	ASTBasePickup();

protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
public:	
	virtual void Tick(float DeltaTime) override;

private:

	float RotationYaw = 0.0f;
	
	virtual bool GivePickupTo(APawn* PlayerPawn);
	void PickupWasTaken();
	void Respawn();
	void GenerateRotationYaw();
};
