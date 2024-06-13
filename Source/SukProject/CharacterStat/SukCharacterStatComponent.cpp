// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/SukCharacterStatComponent.h"
#include "GameData/SukGameDataManager.h"

// Sets default values for this component's properties
USukCharacterStatComponent::USukCharacterStatComponent() : CurrentLevel(1), CurrentHp(0), CurrentExp(0), MaxExp(0), CurrentMoney(0)
{
	CurrentLevel = 1;

	bWantsInitializeComponent = true;
}

void USukCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetLevelStat(CurrentLevel);
	SetHp(BaseStat.MaxHp);
}

void USukCharacterStatComponent::SetLevelStat(int32 InNewLevel)
{

	CurrentLevel = InNewLevel;
	SetBaseStat(USukGameDataManager::Get().GetCharacterStat(CurrentLevel));

}

void USukCharacterStatComponent::SetHp(int32 InNewHp)
{
	CurrentHp = FMath::Clamp(InNewHp, 0, BaseStat.MaxHp + ModifierStat.MaxHp);

}

void USukCharacterStatComponent::LevelUp()
{
	SetLevelStat(CurrentLevel + 1);
}



float USukCharacterStatComponent::ApplyDamage(float InDamage)
{
	float ActualDamage = FMath::Clamp(InDamage, 0, InDamage);
	SetHp(CurrentHp - ActualDamage);

	// CurrentHp가 0이면 delegate로 Dead 호출
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}

	return ActualDamage;
}

float USukCharacterStatComponent::ApplyExp(float InExp)
{
	CurrentExp += InExp;

	if (CurrentExp >= MaxExp)
	{
		CurrentExp =FMath::Clamp(CurrentExp-MaxExp,0,CurrentExp-MaxExp);
		LevelUp();
	}
	
	return CurrentExp;
}

float USukCharacterStatComponent::ApplyMoney(float InMoney)
{
	return 0.0f;
}



