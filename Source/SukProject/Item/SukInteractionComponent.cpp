// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SukInteractionComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Interface/SukActorInteractionInterface.h"
#include "EnhancedInputSubsystems.h"
#include "Character/SukCharacterBase.h"

USukInteractionComponent::USukInteractionComponent()
{
	
	SphereRadius = 80.0f;
	//InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickUpInteractionWidget"));
	// InteractionWidget->SetupAttachment(GetAttachmentRoot());
	//InteractionWidget->AttachToComponent(GetAttachmentRoot(), FAttachmentTransformRules::KeepRelativeTransform);

	
	Owner = GetAttachParentActor();

	//static ConstructorHelpers::FClassFinder<UUserWidget> InteractionWidgetRef (TEXT("/Game/UI/WBP_InteractionWidget.WBP_InteractionWidget_C"));
	//if (InteractionWidgetRef.Class)
	//{
	//	InteractionWidget->SetWidgetClass(InteractionWidgetRef.Class);
	//	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	//	InteractionWidget->SetDrawSize(FVector2D(100.0f, 50.0f));
	//	InteractionWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//}

	//InteractionWidget->SetHiddenInGame(true);

	static ConstructorHelpers::FObjectFinder<UInputAction> InteractionActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Interaction.IA_Interaction'"));
	if (InteractionActionRef.Object)
	{
		InteractionAction = InteractionActionRef.Object;
	}

}

void USukInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register Overlap Events
	OnComponentBeginOverlap.AddDynamic(this, &USukInteractionComponent::OnSphereBeginOverlap);

	OnComponentEndOverlap.AddDynamic(this, &USukInteractionComponent::OnSphereEndOverlap);
}

void USukInteractionComponent::OnRegister()
{
	Super::OnRegister();

	/*InteractionWidget->AttachToComponent(GetAttachmentRoot(), FAttachmentTransformRules::KeepRelativeTransform);
	InteractionWidget->SetRelativeLocation(FVector(0.0f, 2.0f, 0.0f));*/

}

// 캐릭터가 범위 안으로 들어오면서 Input을 바인드한다.
void USukInteractionComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASukCharacterBase* OverlappingActor = Cast<ASukCharacterBase>(OtherActor);
	if (OverlappingActor)
	{
		//InteractionWidget->SetHiddenInGame(false);

		APawn* playerPawn = Cast<APawn>(OtherActor);
		if (playerPawn)
		{
			if (APlayerController* PC = Cast<APlayerController>(playerPawn->GetController()))
			{
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
	ASukCharacterBase* OverlappingActor = Cast<ASukCharacterBase>(OtherActor);
	if (OverlappingActor)
	{
		//InteractionWidget->SetHiddenInGame(true);

		APawn* playerPawn = Cast<APawn>(OtherActor);
		if (playerPawn)
		{
			if (APlayerController* PC = Cast<APlayerController>(playerPawn->GetController()))
			{
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
	ISukActorInteractionInterface* ActorInteraction = Cast<ISukActorInteractionInterface>(Owner);

	if (ActorInteraction)
	{
		ActorInteraction->OwnerInteraction();
	}


	// 상자의 경우 아이템 꺼내기
	UE_LOG(LogTemp, Warning, TEXT("Interaction"));

	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
