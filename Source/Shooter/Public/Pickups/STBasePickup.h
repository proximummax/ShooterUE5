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
	// Sets default values for this actor's properties
	ASTBasePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
