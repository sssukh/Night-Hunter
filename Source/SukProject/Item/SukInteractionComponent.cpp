// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SukInteractionComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Interface/SukInteractionSetupInterface.h"

USukInteractionComponent::USukInteractionComponent()
{
	SphereRadius = 80.0f;
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickUpInteractionWidget"));
	InteractionWidget->SetupAttachment(GetAttachmentRoot());
	InteractionWidget->SetRelativeLocation(FVector(0.0f, 2.0f, 0.0f));
	
	static ConstructorHelpers::FClassFinder<UUserWidget> InteractionWidgetRef (TEXT("/Game/UI/WBP_InteractionWidget.WBP_InteractionWidget_C"));
	if (InteractionWidgetRef.Class)
	{
		InteractionWidget->SetWidgetClass(InteractionWidgetRef.Class);
		InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
		InteractionWidget->SetDrawSize(FVector2D(100.0f, 50.0f));
		InteractionWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	InteractionWidget->SetHiddenInGame(true);
}

void USukInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register Overlap Events
	OnComponentBeginOverlap.AddDynamic(this, &USukInteractionComponent::OnSphereBeginOverlap);

	OnComponentEndOverlap.AddDynamic(this, &USukInteractionComponent::OnSphereEndOverlap);
}

void USukInteractionComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ISukInteractionSetupInterface* OverlappingActor = Cast<ISukInteractionSetupInterface>(OtherActor);
	if (OverlappingActor)
	{
		OverlappingActor->InteractionSetup();
		InteractionWidget->SetHiddenInGame(false);
	}
}

void USukInteractionComponent::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ISukInteractionSetupInterface* OverlappingActor = Cast<ISukInteractionSetupInterface>(OtherActor);
	if (OverlappingActor)
	{
		OverlappingActor->InteractionFinish();
		InteractionWidget->SetHiddenInGame(true);
	}

}

void USukInteractionComponent::Interaction()
{
	// 아이템의 경우 능력이나 능력치 얻기
	
	// 상자의 경우 아이템 꺼내기
}
