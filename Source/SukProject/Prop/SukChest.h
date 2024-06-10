// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SukChest.generated.h"

class USkeletaMeshComponent;
class UBoxComponent;
class AnimMontage;

UCLASS()
class SUKPROJECT_API ASukChest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASukChest();

	FORCEINLINE UBoxComponent* GetTrigger() { return Trigger; }

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere,Category=Chest)
	TObjectPtr<UBoxComponent> Trigger;

	UPROPERTY(EditAnywhere,Category = Chest)
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(EditAnywhere,Category = Montage)
	TObjectPtr<UAnimMontage> OpenMontage;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	UFUNCTION()
	void OpenChest();

	void PlayOpenAnimation();

	bool IsOpened;
};
