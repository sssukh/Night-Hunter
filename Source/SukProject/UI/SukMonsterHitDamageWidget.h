// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SukUserWidget.h"
#include "SukMonsterHitDamageWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUKPROJECT_API USukMonsterHitDamageWidget : public USukUserWidget
{
	GENERATED_BODY()
public:
	USukMonsterHitDamageWidget(const FObjectInitializer& ObjectInitializer);

	void CreateDamageNumberText(float InDamage);
protected:
	virtual void NativeConstruct() override;
};
