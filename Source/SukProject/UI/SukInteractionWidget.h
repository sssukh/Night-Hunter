// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SukInteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUKPROJECT_API USukInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	USukInteractionWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;



	UFUNCTION(BlueprintCallable)
	void SetInteractionText(FString InText);

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Text)
	TObjectPtr<class UTextBlock> InteractionText;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Image)
	TObjectPtr<class UImage> InteractionImage;
};
