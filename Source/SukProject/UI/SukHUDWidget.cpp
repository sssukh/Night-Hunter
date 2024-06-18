// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SukHUDWidget.h"
#include "SukHpWidget.h"

USukHUDWidget::USukHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void USukHUDWidget::UpdateHpBar(float NewCurrentHp)
{
	HpBar->UpdateHpBar(NewCurrentHp);
}

void USukHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<USukHpWidget>(GetWidgetFromName(TEXT("WidgetHpBar")));
}
