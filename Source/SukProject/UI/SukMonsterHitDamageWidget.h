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

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetDamage(float InDamage) {Damage = InDamage;}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetDamage() { return Damage; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetInitPos(FVector2D InInitpos) { InitPosition = InInitpos; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetDestPos(FVector2D InDestPos) { DestPosition = InDestPos; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FVector2D GetInitPos() { return InitPosition; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FVector2D GetDestPos() { return DestPosition; }

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere)
	float Damage=0;

	UPROPERTY(EditAnywhere)
	FVector2D InitPosition;

	UPROPERTY(EditAnywhere)
	FVector2D DestPosition;

	UPROPERTY()
	TObjectPtr<class UTextBlock> DamageTextWidget;

};
