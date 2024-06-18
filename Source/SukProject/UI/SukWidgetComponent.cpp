// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SukWidgetComponent.h"
#include "SukUserWidget.h"

void USukWidgetComponent::InitWidget()
{
	Super::InitWidget();

	USukUserWidget* UserWidget = Cast<USukUserWidget>(GetWidget());
	if (UserWidget)
	{
		UserWidget->SetOwningActor(GetOwner());
	}
}
