// Shooter, All Rights Reserved


#include "Pickups/STBasePickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickUp,All,All);
// Sets default values
ASTBasePickup::ASTBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

// Called when the game starts or when spawned
void ASTBasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASTBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UE_LOG(LogBasePickUp,Display,TEXT("Actor is overlap"));
	Destroy(OtherActor);
}

// Called every frame
void ASTBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

