// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SukItem.h"
#include "SukInteractionComponent.h"

// Sets default values
ASukItem::ASukItem()
{
	InteractionComponent=CreateDefaultSubobject<USukInteractionComponent>(TEXT("ItemInteractionComponent"));
	InteractionComponent->SetSphereRadius(100.0f);
	RootComponent = InteractionComponent;

	PrimaryActorTick.bCanEverTick = true;

	TurnRate = 10.0f;
}

void ASukItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SetInteractionComponentOwner(this);
}

void ASukItem::OwnerInteraction()
{

}

void ASukItem::Tick(float DeltaTime)
{
	FRotator Rotator = FRotator::ZeroRotator;
	Rotator.Yaw = DeltaTime * TurnRate;
	AddActorLocalRotation(Rotator);
}

void ASukItem::SetInteractionComponentOwner(AActor* InOwner)
{
	InteractionComponent->SetOwner(InOwner);
}



