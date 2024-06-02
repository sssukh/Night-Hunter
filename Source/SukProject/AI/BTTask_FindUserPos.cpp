// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindUserPos.h"
#include "SukAI.h"	
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/SukCharacterAIInterface.h"


UBTTask_FindUserPos::UBTTask_FindUserPos()
{
}

EBTNodeResult::Type UBTTask_FindUserPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (nullptr == Target)
	{
		return EBTNodeResult::Failed;
	}

	float DistanceToTarget = ControllingPawn->GetDistanceTo(Target);
	
	

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_PATROLPOS, Target->GetNavAgentLocation());

	return EBTNodeResult::Succeeded;
}
