// Shooter, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/STBaseCharacter.h"
#include "STAICharacter.generated.h"

class UBehaviorTree;
UCLASS()
class SHOOTER_API ASTAICharacter : public ASTBaseCharacter
{
	GENERATED_BODY()
public:
	ASTAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
	UBehaviorTree* BehaviorTree;

protected:
	virtual void OnDeath() override;
};
