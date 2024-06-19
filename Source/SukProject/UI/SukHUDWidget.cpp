// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SukHUDWidget.h"
#include "SukHpWidget.h"
#include "SukUserWidget.h"
#include "Interface/SukCharacterHUDInterface.h"

USukHUDWidget::USukHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void USukHUDWidget::UpdateHpBar(float InCurrentHp, float InMaxHp)
{
	HpBar->UpdateHpBar(InCurrentHp,InMaxHp);
}

void USukHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<USukHpWidget>(GetWidgetFromName(TEXT("WidgetHpBar")));
	ensure(HpBar);

	Crosshair = Cast<USukUserWidget>(GetWidgetFromName(TEXT("Crosshair")));
	ensure(Crosshair);

	ISukCharacterHUDInterface* CharacterHUDInterface = Cast<ISukCharacterHUDInterface>(GetOwningPlayerPawn());
	if (CharacterHUDInterface)
	{
		CharacterHUDInterface->SetupCharacterHpBar(this);
	}
}
