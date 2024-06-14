// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/SukCharacterExpInterface.h"
#include "SukCharacterBase.generated.h"

class USukCharacterControlData;
class UAnimMontage;
class USukCharacterStatComponent;

UENUM()
enum class ECharacterControlType : uint8
{
	Default,
	HoldingWeapon
};

UCLASS()
class SUKPROJECT_API ASukCharacterBase : public ACharacter, public ISukCharacterExpInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASukCharacterBase();

	virtual void BeginPlay() override;

	// Dead Section
	virtual void SetDead();
	void PlayDeadAnimation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> DeadMontage;
	
	float DeadEventDelayTime = 5.0f;

	// interaction
public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void GetExp(float InExp) override;

public:
	TObjectPtr<USukCharacterStatComponent> Stat;

protected:
	TObjectPtr<AActor> CharacterLastHitter;
};
