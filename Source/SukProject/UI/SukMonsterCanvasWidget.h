// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SukMonsterCanvasWidget.generated.h"

class UCanvasPanel;
/**
 * 
 */
UCLASS()
class SUKPROJECT_API USukMonsterCanvasWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	USukMonsterCanvasWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UCanvasPanel* GetDamageCanvas() {return DamageCanvas;}

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	TObjectPtr<UCanvasPanel> DamageCanvas;

};
