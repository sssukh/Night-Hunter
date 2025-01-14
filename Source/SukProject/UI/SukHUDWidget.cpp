// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SukHUDWidget.h"
#include "SukHpWidget.h"
#include "SukUserWidget.h"
#include "Interface/SukCharacterHUDInterface.h"
#include "SukCrosshairWidget.h"

USukHUDWidget::USukHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void USukHUDWidget::UpdateHpBar(float InCurrentHp, float InMaxHp)
{
	HpBar->UpdateHpBar(InCurrentHp,InMaxHp);
}

void USukHUDWidget::CrosshairShowHit()
{
	Crosshair->CrosshairShowHit();
}

void USukHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<USukHpWidget>(GetWidgetFromName(TEXT("WidgetHpBar")));
	ensure(HpBar);

	// UpdateHpBar의 ensure를 넘어가기 위한 임시값.
	HpBar->SetMaxHp(100.0f);

	Crosshair = Cast<USukCrosshairWidget>(GetWidgetFromName(TEXT("WidgetCrosshair")));
	ensure(Crosshair);

	ISukCharacterHUDInterface* CharacterHUDInterface = Cast<ISukCharacterHUDInterface>(GetOwningPlayerPawn());
	if (CharacterHUDInterface)
	{
		CharacterHUDInterface->SetupCharacterHUDWidget(this);
	}
}
