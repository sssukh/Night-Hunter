// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/SukCharacterAIInterface.h"
#include "Interface/SukMonsterInterface.h"
#include "Interface/SukGMAnimationInterface.h"
#include "SukMonsterBase.generated.h"


UCLASS()
class SUKPROJECT_API ASukMonsterBase : public ACharacter, public ISukCharacterAIInterface, public ISukMonsterInterface, public ISukGMAnimationInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASukMonsterBase();

	virtual void BeginPlay() override;

	// AI Interface
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	// Attack
	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;
	virtual void AttackEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded);

	FAICharacterAttackFinished OnAttackFinished;

	virtual void AttackHitCheck();

	

	// Got Hit
	virtual void GetDamaged(float inDamage) override;

	// Dead
	virtual void SetDead();
	void PlayDeadMontage();

	float DeadEventDelayTime = 3.0f;

	// Spawn
	virtual void Spawn();
	void PlaySpawnMontage();
	void SetSpawnedMonster(UAnimMontage* TargetMontage, bool IsProperlyEnded);

	// Animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
	TObjectPtr<UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
	TObjectPtr<UAnimMontage> SpawnMontage;
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Stat)
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Speed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Hp;

};
