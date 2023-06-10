#pragma once

#include "CoreTypes.generated.h"
class ASTBaseWeapon;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, ASTBaseWeapon*);

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Weapon")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Weapon", meta = (EditCondition = "!Infinite"))
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Weapon")
	bool Infinite;
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Weapon")
	TSubclassOf<ASTBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Weapon")
	UAnimMontage* ReloadAnimMontage;
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UI")
	UTexture2D* MainIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UI")
	UTexture2D* CrossHairIcon;
};
// VFX

class UNiagaraSystem;
USTRUCT(BlueprintType)
struct FDecalData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "VFX")
	UMaterialInterface* Material;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "VFX")
	FVector Size = FVector(10.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "VFX")
	float LifeTime = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "VFX")
	float FadeOutTime = 0.7f;
};

USTRUCT(BlueprintType)
struct FImpactData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "VFX")
	UNiagaraSystem* NiagaraEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "VFX")
	FDecalData DecalData;
};

USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int32 PlayersNum = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int32 RoundsNum = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int32 RoundTime = 10; // in seconds

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor DefaultTeamColor = FLinearColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FLinearColor> TeamColors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int32 RespawnTime = 5; // in seconds
};

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float);
