// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/SukCharacterStat.h"
#include "SukCharacterStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUKPROJECT_API USukCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USukCharacterStatComponent();

	virtual void InitializeComponent() override;
public:
	void SetLevelStat(int32 InNewLevel);

	void SetHp(int32 InNewHp);

	float ApplyDamage(float InDamage);

	float ApplyExp(float InExp);

	float ApplyMoney(float InMoney);

	FORCEINLINE float GetCurrentLevel() const { return CurrentLevel; }
	FORCEINLINE void AddBaseStat(const FSukCharacterStat& InAddBaseStat) { BaseStat = BaseStat + InAddBaseStat; }

protected:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;
	
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentExp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentLevel;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentMoney;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FSukCharacterStat BaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FSukCharacterStat ModifierStat;
};
