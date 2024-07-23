// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/SukActorInteractionInterface.h"
#include "GameFramework/Actor.h"
#include "SukPickup.generated.h"

UCLASS()
class SUKPROJECT_API ASukPickup : public AActor, public ISukActorInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASukPickup();


protected:
	// Action will be defined by Blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = Interaction, Meta = (DisplayName = "Interaction_Cpp"))
	void K2_Interaction();

	
	// Interface
	virtual void OwnerInteraction() override;
	virtual void SetInteractionComponentOwner(AActor* InOwner) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class USukInteractionComponent> InteractionComponent;

};
