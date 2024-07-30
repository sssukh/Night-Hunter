// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SukPickup.h"
#include "SukInteractionComponent.h"
#include "Player/SukPlayerController.h"
#include "Character/SukCharacterBase.h"

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

	// 이게 문제임..
	ASukCharacterBase* Character = InteractionComponent->GetRangedActor();
	ASukPlayerController* PC = Cast<ASukPlayerController>(Character->GetController());

	PC->AddItem(Itemcpp);

	Destroy();
}

void ASukPickup::SetInteractionComponentOwner(AActor* InOwner)
{
	InteractionComponent->SetOwner(InOwner);
}



