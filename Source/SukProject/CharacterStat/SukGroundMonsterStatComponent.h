// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/SukGroundMonsterStat.h"
#include "SukGroundMonsterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnMonsterHpZero);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHpChangeDelegate, float /*CurrentHp*/,float /*MaxHp*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUKPROJECT_API USukGroundMonsterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USukGroundMonsterStatComponent();

	virtual void InitializeComponent() override;

	FOnMonsterHpZero OnMonsterHpZero;
	FOnHpChangeDelegate OnMonsterHpChange;

	void SetLevelStat(int32 InLevel);

	void SetHp(float InHp);

	void ApplyDamage(float InDamage);

	FORCEINLINE void SetGroundMonsterStat(const FSukGroundMonsterStat& InStat) { MonsterStat = InStat; }
	FORCEINLINE float GetMaxHp() { return MonsterStat.MaxHp; }
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }

public:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentLevel;

	UPROPERTY(VisibleInstanceOnly,Category =Stat)
	int32 MaxLevel;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FSukGroundMonsterStat MonsterStat;
	

};
