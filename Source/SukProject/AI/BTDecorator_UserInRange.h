// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_UserInRange.generated.h"

/**
 * 
 */
UCLASS()
class SUKPROJECT_API UBTDecorator_UserInRange : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_UserInRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
