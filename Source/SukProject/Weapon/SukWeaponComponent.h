// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ActorComponent.h"
#include "Player/SukCharacterPlayer.h"
#include "SukWeaponComponent.generated.h"




class ASukProjectile;
class UInputAction;
class ASukCharacterPlayer;

UENUM()
enum class EFireType : uint8
{
	LineTrace UMETA(DisplayName = "Line Trace"),
	Projectile UMETA(DisplayName = "Projectile")
};

/**
 * 
 */
UCLASS()
class SUKPROJECT_API USukWeaponComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	USukWeaponComponent();

	
	AController* GetCharacterController() { return OwnerCharacter->GetController(); }

	ASukCharacterPlayer* GetOwnerCharacter() { return OwnerCharacter; }

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<ASukProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* CharacterFireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;
	


	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void EndFire();


	// Stat
	UPROPERTY(EditAnywhere, Category = WeaponStat)
	float AttackRange;

	UPROPERTY(EditAnywhere, Category = WeaponStat)
	float AttackDamage;

	UPROPERTY(EditAnywhere, Category = WeaponStat)
	float FireInterval;

	void SetAttackDamage(const float InAttDamage) { AttackDamage = InAttDamage; }

protected:

	FTransform GetTargetingTransform();

	// Owner
	TObjectPtr<ASukCharacterPlayer> OwnerCharacter;
};