// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SukPickUpComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"

USukPickUpComponent::USukPickUpComponent()
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

void USukPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register Overlap Events
	OnComponentBeginOverlap.AddDynamic(this, &USukPickUpComponent::OnSphereBeginOverlap);

	OnComponentEndOverlap.AddDynamic(this, &USukPickUpComponent::OnSphereEndOverlap);
}

void USukPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	InteractionWidget->SetHiddenInGame(false);
}

void USukPickUpComponent::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InteractionWidget->SetHiddenInGame(true);
}
