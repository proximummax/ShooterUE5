// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STAIController.generated.h"

class USTAIPerceptionComponent;
class USTRespawnComponent;
UCLASS()
class SHOOTER_API ASTAIController : public AAIController
{
	GENERATED_BODY()
public:
	ASTAIController();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
	USTAIPerceptionComponent* STPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
	USTRespawnComponent* STRespawnComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FName FocusOnKeyName = "EnemyActor";
	
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;
private:
	AActor* GetFocusOnActor() const;
};
