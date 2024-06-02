// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/SukCharacterAnimInterface.h"
#include "SukCharacterBase.generated.h"

class USukCharacterControlData;
class UAnimMontage;

UENUM()
enum class ECharacterControlType : uint8
{
	Default,
	HoldingWeapon
};

UCLASS()
class SUKPROJECT_API ASukCharacterBase : public ACharacter, public ISukCharacterAnimInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASukCharacterBase();

	// Dead Section
	virtual void SetDead();
	void PlayDeadAnimation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> DeadMontage;
	
	float DeadEventDelayTime = 5.0f;


public:
	virtual void TakeDamage();

};
