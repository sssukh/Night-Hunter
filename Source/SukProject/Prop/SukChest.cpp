// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/SukChest.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Item/SukInteractionComponent.h"
#include "Physics/SukPhysics.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"


// Sets default values
ASukChest::ASukChest()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	RootComponent = Box;
	Mesh->SetupAttachment(RootComponent);

	Mesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	IsOpened = false;

	ChestInteractionComponent = CreateDefaultSubobject<USukInteractionComponent>(TEXT("InteractionComponent"));
	ChestInteractionComponent->SetupAttachment(RootComponent);
	ChestInteractionComponent->SetSphereRadius(140.0f);
}

void ASukChest::SetInteractionComponentOwner(AActor* InOwner)
{
	ChestInteractionComponent->SetOwner(InOwner);
}

void ASukChest::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SetInteractionComponentOwner(this);
}


void ASukChest::OpenChest()
{
	PlayOpenAnimation();
}

void ASukChest::PlayOpenAnimation()
{
	if (!IsOpened)
	{
		UAnimInstance* AnimInstance = Cast<UAnimInstance>(Mesh->GetAnimInstance());
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(OpenMontage, 1.5f);

			/*FOnMontageEnded ChestOpenEnded;
			ChestOpenEnded.BindUObject(this, &ASukChest::CreateItemInBox);

			AnimInstance->Montage_SetEndDelegate(ChestOpenEnded, OpenMontage);*/
		}

		IsOpened = true;
	}
}

void ASukChest::OwnerInteraction()
{
	OpenChest();
}

void ASukChest::CreateItemInBox(UAnimMontage* InMontage, bool bInterrupted)
{
	K2_AfterChestOpen();
}






