// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SukInteractionComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Interface/SukInteractionSetupInterface.h"
#include "EnhancedInputSubsystems.h"

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

// 캐릭터가 범위 안으로 들어오면서 Input을 바인드한다.
void USukInteractionComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ISukInteractionSetupInterface* OverlappingActor = Cast<ISukInteractionSetupInterface>(OtherActor);
	if (OverlappingActor)
	{
		OverlappingActor->InteractionSetup();
		InteractionWidget->SetHiddenInGame(false);

		APawn* playerPawn = Cast<APawn>(OtherActor);
		if (playerPawn)
		{
			if (APlayerController* PC = Cast<APlayerController>(playerPawn->GetController()))
			{
				// UEnhancedInput 헤더 필요함.
				// Interaction 바인드하면 될것같긴하다.
				if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PC->InputComponent))
				{
					EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Triggered, this, &USukInteractionComponent::Interaction);
					InteractionBindingIndex = EnhancedInputComponent->GetActionEventBindings().Num() - 1;
				}
			}
			
		}
	}
}

// 캐릭터가 범위 밖으로 나가면서 바인드한 Input을 제거한다.
void USukInteractionComponent::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ISukInteractionSetupInterface* OverlappingActor = Cast<ISukInteractionSetupInterface>(OtherActor);
	if (OverlappingActor)
	{
		OverlappingActor->InteractionFinish();
		InteractionWidget->SetHiddenInGame(true);

		APawn* playerPawn = Cast<APawn>(OtherActor);
		if (playerPawn)
		{
			if (APlayerController* PC = Cast<APlayerController>(playerPawn->GetController()))
			{
				// UEnhancedInput 헤더 필요함.
				// Interaction 바인드하면 될것같긴하다.
				if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PC->InputComponent))
				{
					if (EnhancedInputComponent->RemoveActionEventBinding(InteractionBindingIndex))
					{
						UE_LOG(LogTemp, Warning, TEXT("Binding Removed"));
					}
				}
			}

		}
	}
}

void USukInteractionComponent::Interaction()
{
	// 아이템의 경우 능력이나 능력치 얻기
	
	// 상자의 경우 아이템 꺼내기
	UE_LOG(LogTemp, Warning, TEXT("Interaction"));
}
