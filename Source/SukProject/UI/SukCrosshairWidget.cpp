// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SukCrosshairWidget.h"
#include "Components/Image.h"

USukCrosshairWidget::USukCrosshairWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void USukCrosshairWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MainCrosshair = Cast<UImage>(GetWidgetFromName("MainCrosshair"));
	ensure(MainCrosshair);

	HitCrosshair = Cast<UImage>(GetWidgetFromName("HitCrosshair"));
	ensure(HitCrosshair);
}
