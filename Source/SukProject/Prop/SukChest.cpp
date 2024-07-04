// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/SukChest.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Item/SukInteractionComponent.h"
#include "Physics/SukPhysics.h"


// Sets default values
ASukChest::ASukChest()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);

	// 트리거 만들고 여기에 등록하기.
	Trigger->SetCollisionProfileName(CPROFILE_CHEST);
	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));

	Mesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	IsOpened = false;

	ChestInteractionComponent = CreateDefaultSubobject<USukInteractionComponent>(TEXT("InteractionComponent"));
	ChestInteractionComponent->SetupAttachment(RootComponent);
	ChestInteractionComponent->SetOwner(this);
	ChestInteractionComponent->SetSphereRadius(140.0f);

}

void ASukChest::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASukChest::OnOverlapBegin);
}



void ASukChest::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	PlayOpenAnimation();
}

void ASukChest::OpenChest()
{

}

void ASukChest::PlayOpenAnimation()
{
	if (!IsOpened)
	{
		UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
		AnimInstance->Montage_Play(OpenMontage, 1.5f);

		IsOpened = true;
	}
}

void ASukChest::OwnerInteraction()
{
	PlayOpenAnimation();
}




