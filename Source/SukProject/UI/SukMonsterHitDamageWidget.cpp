// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SukMonsterHitDamageWidget.h"
#include "Components/TextBlock.h"

USukMonsterHitDamageWidget::USukMonsterHitDamageWidget(const FObjectInitializer& ObjectInitializer)
{
}



void USukMonsterHitDamageWidget::NativeConstruct()
{
	DamageTextWidget = Cast<UTextBlock>(GetWidgetFromName(TEXT("DamageText")));
	ensure(DamageTextWidget);

}
