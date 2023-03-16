// Shooter, All Rights Reserved


#include "Pickups/STBasePickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickUp, All, All);

ASTBasePickup::ASTBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

void ASTBasePickup::BeginPlay()
{
	Super::BeginPlay();
	check(CollisionComponent);

	GenerateRotationYaw();
}

void ASTBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if (!Pawn)
		return;

	if (GivePickupTo(Pawn))
		PickupWasTaken();
	
}

void ASTBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f,RotationYaw,0.0f));
}

bool ASTBasePickup::CouldBeTaken() const
{
	return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}

bool ASTBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void ASTBasePickup::PickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	if (!GetRootComponent())
		return;

	GetRootComponent()->SetVisibility(false, true);

	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTBasePickup::Respawn, RespawnTime);
}

void ASTBasePickup::Respawn()
{
	GenerateRotationYaw();
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	if (!GetRootComponent())
		return;

	GetRootComponent()->SetVisibility(true, true);
}

void ASTBasePickup::GenerateRotationYaw()
{
	const auto Direction = FMath::RandBool() ? 1.0 : -1.0;
	RotationYaw = FMath::RandRange(1.0f,2.0f) * Direction;
	
}
