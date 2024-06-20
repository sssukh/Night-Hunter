// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SukCrosshairWidget.h"
#include "Components/Image.h"

USukCrosshairWidget::USukCrosshairWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void USukCrosshairWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MainCrosshairWidget = Cast<UImage>(GetWidgetFromName("MainCrosshair"));
	ensure(MainCrosshairWidget);

	HitCrosshairWidget = Cast<UImage>(GetWidgetFromName("HitCrosshair"));
	ensure(HitCrosshairWidget);

	HitCrosshairWidget->SetOpacity(0.0f);
}



void USukCrosshairWidget::CrosshairShowHit()
{
	// HitCrosshair가 나타났다가 사라진다.
	UE_LOG(LogTemp, Warning, TEXT("CrossHairShowHit"));
	HitCrosshairWidget->SetOpacity(1.0f);
}
