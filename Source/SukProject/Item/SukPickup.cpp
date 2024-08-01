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

	PrimaryActorTick.bCanEverTick = true;

}

void ASukPickup::BeginPlay()
{
	Super::BeginPlay();
}

void ASukPickup::OwnerInteraction()
{
	K2_Interaction();

	// InteractionComponent에서 interact해서 여기로 넘어옴.
	// 필요한건 PlayerController를 얻는 것.

	// 이게 문제임..
	/*ASukCharacterBase* Character = InteractionComponent->GetRangedActor();
	ASukPlayerController* PC = Cast<ASukPlayerController>(Character->GetController());

	PC->AddItem(Itemcpp);*/

	Destroy();
}

void ASukPickup::SetInteractionComponentOwner(AActor* InOwner)
{
	InteractionComponent->SetOwner(InOwner);
}



