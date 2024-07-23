// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SukPickup.h"
#include "SukInteractionComponent.h"

// Sets default values
ASukPickup::ASukPickup()
{
 	
	InteractionComponent = CreateDefaultSubobject<USukInteractionComponent>(TEXT("InteractionComponent"));
	InteractionComponent->SetupAttachment(RootComponent);
	InteractionComponent->SetSphereRadius(140.0f);

	SetInteractionComponentOwner(this);
}

void ASukPickup::OwnerInteraction()
{
	K2_Interaction();
}

void ASukPickup::SetInteractionComponentOwner(AActor* InOwner)
{
	InteractionComponent->SetOwner(InOwner);
}



