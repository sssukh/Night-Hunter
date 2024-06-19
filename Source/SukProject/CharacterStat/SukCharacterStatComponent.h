// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/SukCharacterStat.h"
#include "GameData/SukCharacterExp.h"
#include "SukCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHpChangedDelegate, float/*CurrentHp*/,float/*MaxHp*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUKPROJECT_API USukCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USukCharacterStatComponent();

	virtual void InitializeComponent() override;
public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;

	void SetLevelStat(int32 InNewLevel);

	void SetHp(int32 InNewHp);

	void LevelUp();

	float ApplyDamage(float InDamage);

	float ApplyExp(float InExp);

	float ApplyMoney(float InMoney);

	FORCEINLINE float GetCurrentLevel() const { return CurrentLevel; }
	FORCEINLINE void AddBaseStat(const FSukCharacterStat& InAddBaseStat) { BaseStat = BaseStat + InAddBaseStat; }
	FORCEINLINE void SetBaseStat(const FSukCharacterStat& InBaseStat) { BaseStat = InBaseStat; }
	FORCEINLINE const FSukCharacterStat GetStat() { return BaseStat + ModifierStat; }
	FORCEINLINE float GetMaxHp() { return MaxHp + ModifierStat.MaxHp; }
	FORCEINLINE const float GetMaxExp() { return MaxExp; }
	FORCEINLINE const float GetCurrentHp() { return CurrentHp; }

protected:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;
	
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float MaxHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentExp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float MaxExp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentLevel;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentMoney;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FSukCharacterStat BaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FSukCharacterStat ModifierStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FSukCharacterExp ExpData;
};
