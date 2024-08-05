// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/SukActorInteractionInterface.h"
#include "SukChest.generated.h"

class USkeletaMeshComponent;
class UBoxComponent;
class AnimMontage;

UCLASS()
class SUKPROJECT_API ASukChest : public AActor, public ISukActorInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASukChest();

	virtual void SetInteractionComponentOwner(AActor* InOwner) override; 


	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere,Category=Chest)
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(EditAnywhere,Category = Chest)
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(EditAnywhere,Category = Montage)
	TObjectPtr<UAnimMontage> OpenMontage;


	UFUNCTION()
	void OpenChest();

	UFUNCTION(BlueprintCallable)
	void PlayOpenAnimation();

	bool IsOpened;

	virtual void OwnerInteraction(APlayerController* InPlayerController) override;


	// Action will be defined by Blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = Interaction, Meta = (DisplayName = "ChestOpened"))
	void K2_AfterChestOpen();

	void CreateItemInBox(UAnimMontage* InMontage, bool bInterrupted);

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class USukInteractionComponent> ChestInteractionComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Item)
	TSubclassOf<class ASukPickup> ItemPickup;
};
