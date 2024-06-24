// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SukHpWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/ActorHpBarWidgetInterface.h"

USukHpWidget::USukHpWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.0f;
}

void USukHpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbHpBar")));
	ensure(HpProgressBar);
	IActorHpBarWidgetInterface* HpBarWidget = Cast<IActorHpBarWidgetInterface>(OwningActor);
	if (HpBarWidget)
	{
		HpBarWidget->SetupHpBarWidget(this);
	}
}

void USukHpWidget::UpdateHpBar(float InCurrentHp, float InMaxHp)
{
	ensure(MaxHp > 0.0f);
	if (HpProgressBar)
	{
		SetMaxHp(InMaxHp);
		HpProgressBar->SetPercent(InCurrentHp / InMaxHp);
	}
}
