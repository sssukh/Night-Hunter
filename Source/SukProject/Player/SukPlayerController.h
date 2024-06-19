// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SukPlayerController.generated.h"

class USukUserWidget;
class USukHUDWidget;
/**
 * 
 */
UCLASS()
class SUKPROJECT_API ASukPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASukPlayerController();


protected:
	virtual void BeginPlay() override;

	// HUD section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<USukHUDWidget> SukHUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TObjectPtr<USukHUDWidget> SukHUDWidget;
};
