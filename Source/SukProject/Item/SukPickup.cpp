// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SukPickup.h"
#include "SukInteractionComponent.h"
#include "Player/SukPlayerController.h"
#include "Character/SukCharacterBase.h"
#include "Player/SukPlayerController.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


// Sets default values
ASukPickup::ASukPickup()
{
 	
	InteractionComponent = CreateDefaultSubobject<USukInteractionComponent>(TEXT("InteractionComponent"));
	SetRootComponent(InteractionComponent);
	InteractionComponent->SetSphereRadius(140.0f);

	SetInteractionComponentOwner(this);

	
	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemStaticMesh"));
	ItemStaticMesh->SetupAttachment(RootComponent);
}

void ASukPickup::BeginPlay()
{
	Super::BeginPlay();
	
	// ItemStaticMesh->SetStaticMesh(Itemcpp->Mesh);
}

void ASukPickup::PreInitializeComponents()
{
	Super::PreInitializeComponents();

}

void ASukPickup::OwnerInteraction(APlayerController* InPlayerController)
{
	K2_Interaction();

	ASukPlayerController* PlayerController = Cast<ASukPlayerController>(InPlayerController);
	if (PlayerController)
	{
		PlayerController->AddItem(Itemcpp);
	}

	Destroy();
}

void ASukPickup::SetInteractionComponentOwner(AActor* InOwner)
{
	InteractionComponent->SetOwner(InOwner);
}




