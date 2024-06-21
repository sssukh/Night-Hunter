// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SukMonsterCanvasWidget.h"
#include "Components/CanvasPanel.h"

USukMonsterCanvasWidget::USukMonsterCanvasWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void USukMonsterCanvasWidget::NativeConstruct()
{
	Super::NativeConstruct();

	DamageCanvas = Cast<UCanvasPanel>(GetWidgetFromName("CanvasPanel"));
	ensure(DamageCanvas);
}
