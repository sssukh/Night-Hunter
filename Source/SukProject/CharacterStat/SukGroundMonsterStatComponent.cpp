// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/SukGroundMonsterStatComponent.h"
#include "GameData/SukGameDataManager.h"

// Sets default values for this component's properties
USukGroundMonsterStatComponent::USukGroundMonsterStatComponent()
{
	MaxLevel = 5;
	CurrentLevel = 1;

	bWantsInitializeComponent = true;
}

void USukGroundMonsterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetLevelStat(CurrentLevel);
	SetHp(MonsterStat.MaxHp);
}

void USukGroundMonsterStatComponent::SetLevelStat(int32 InLevel)
{
	CurrentLevel = FMath::Clamp(InLevel, 1, MaxLevel);
	SetGroundMonsterStat(USukGameDataManager::Get().GetGroundMonsterStat(InLevel));
}

void USukGroundMonsterStatComponent::SetHp(float InHp)
{
	CurrentHp = FMath::Clamp(InHp, 0, MonsterStat.MaxHp);
}

void USukGroundMonsterStatComponent::ApplyDamage(float InDamage)
{
	float ActualDamage = FMath::Clamp(InDamage, 0, InDamage);

	SetHp(CurrentHp - ActualDamage);

	UE_LOG(LogTemp, Error, TEXT("CurrentHp : %f, ActualDamage : %f"), CurrentHp, ActualDamage);

	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnMonsterHpZero.Broadcast();
	}

}


