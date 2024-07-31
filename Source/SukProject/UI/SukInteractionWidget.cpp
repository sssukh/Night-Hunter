// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SukInteractionWidget.h"
#include "Components/TextBlock.h"

USukInteractionWidget::USukInteractionWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void USukInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InteractionText = Cast<UTextBlock>(GetWidgetFromName("InteractionTB"));
	ensure(InteractionText);

}

void USukInteractionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void USukInteractionWidget::SetInteractionText(FString InText)
{
	InteractionText->SetText(FText::FromString(InText));
}


