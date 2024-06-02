// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_UserInRange.h"
#include "AIController.h"
#include "SukAI.h"	
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/SukCharacterAIInterface.h"

UBTDecorator_UserInRange::UBTDecorator_UserInRange()
{
	NodeName = TEXT("IsUserInRange");
}

bool UBTDecorator_UserInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return false;
	}

	ISukCharacterAIInterface* AIPawn = Cast<ISukCharacterAIInterface>(ControllingPawn);
	if (AIPawn == nullptr)
	{
		return false;
	}

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (Target == nullptr)
	{
		return false;
	}

	float DistanceToTarget = ControllingPawn->GetDistanceTo(Target);
	float AttackRangeWithRadius = AIPawn->GetAIAttackRange();
	bResult = (DistanceToTarget <= AttackRangeWithRadius);

	return bResult;
}
