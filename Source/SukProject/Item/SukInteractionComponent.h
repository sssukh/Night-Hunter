// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "EnhancedInputComponent.h"
#include "SukInteractionComponent.generated.h"



/**
 * 
 */
UCLASS()
class SUKPROJECT_API USukInteractionComponent : public USphereComponent
{
	GENERATED_BODY()
public:
	USukInteractionComponent();

	FORCEINLINE void SetOwner(AActor* InOwner) { Owner = InOwner; }

	FORCEINLINE AActor* GetOwner() { return Owner; }

	FORCEINLINE class ASukCharacterBase* GetRangedActor() { return InRangedActor; }

	
protected:
	virtual void BeginPlay() override;

	virtual void OnRegister() override;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void Interaction();



protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> InteractionWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractionAction;

	int32 InteractionBindingIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class ASukCharacterBase> InRangedActor;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TObjectPtr<UUserWidget> WidgetInstance;

	UPROPERTY()
	TObjectPtr<AActor> Owner;
};
