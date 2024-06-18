// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SukHpWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/MonsterWidgetInterface.h"

USukHpWidget::USukHpWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.0f;
}

void USukHpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbHpBar")));
	ensure(HpProgressBar);
	IMonsterWidgetInterface* MonsterWidget = Cast<IMonsterWidgetInterface>(OwningActor);
	if (MonsterWidget)
	{
		MonsterWidget->SetupMonsterWidget(this);
	}
}

void USukHpWidget::UpdateHpBar(float NewCurrentHp)
{
	ensure(MaxHp > 0.0f);
	if (HpProgressBar)
	{
		HpProgressBar->SetPercent(NewCurrentHp / MaxHp);
	}
}
