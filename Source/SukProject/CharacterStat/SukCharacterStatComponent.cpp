// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/SukCharacterStatComponent.h"

// Sets default values for this component's properties
USukCharacterStatComponent::USukCharacterStatComponent()
{
	CurrentLevel = 1;

	bWantsInitializeComponent = true;
}

void USukCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();


}

void USukCharacterStatComponent::SetLevelStat(int32 InNewLevel)
{
	CurrentLevel = InNewLevel;

}

void USukCharacterStatComponent::SetHp(int32 InNewHp)
{

}

float USukCharacterStatComponent::ApplyDamage(float InDamage)
{
	return 0.0f;
}

float USukCharacterStatComponent::ApplyExp(float InExp)
{
	return 0.0f;
}

float USukCharacterStatComponent::ApplyMoney(float InMoney)
{
	return 0.0f;
}



