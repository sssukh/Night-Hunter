// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_TrackingUser.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "SukAI.h"
#include "Interface/SukCharacterAIInterface.h"

UBTService_TrackingUser::UBTService_TrackingUser()
{
	NodeName = TEXT("Tracking");
	Interval = 1.0f;
}

void UBTService_TrackingUser::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingPawn == nullptr)
	{
		return;
	}

	ISukCharacterAIInterface* AIPawn = Cast<ISukCharacterAIInterface>(ControllingPawn);
	if (AIPawn == nullptr)
	{
		return;
	}


	APawn* Player = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!Player->GetActorEnableCollision())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, Player);
	
	float DistanceToTarget = ControllingPawn->GetDistanceTo(Player);

	float Range = AIPawn->GetAIAttackRange();

	bool IsInRange = (DistanceToTarget <= Range);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_INRANGE, IsInRange);

	
}
