// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/SukActorInteractionInterface.h"
#include "GameData/SukCharacterStat.h"
#include "SukItem.generated.h"



UCLASS()
class SUKPROJECT_API ASukItem : public AActor, public ISukActorInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASukItem();


protected:
	virtual void PostInitializeComponents() override;

	virtual void OwnerInteraction() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY()
	TObjectPtr<class USukInteractionComponent> InteractionComponent;

	UPROPERTY()
	FSukCharacterStat UpgradeCharacterStat;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float TurnRate;

private:
	virtual void SetInteractionComponentOwner(AActor* InOwner) override;

};
