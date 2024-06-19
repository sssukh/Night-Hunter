// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SukUserWidget.h"
#include "SukHpWidget.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS()
class SUKPROJECT_API USukHpWidget : public USukUserWidget
{
	GENERATED_BODY()
public:
	USukHpWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateHpBar(float InCurrentHp, float InMaxHp);


protected:
	UPROPERTY()
	TObjectPtr<UProgressBar> HpProgressBar;

	UPROPERTY()
	float MaxHp;

};
