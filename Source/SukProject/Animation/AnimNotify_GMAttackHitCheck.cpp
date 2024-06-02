// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_GMAttackHitCheck.h"
#include "Interface/SukGMAnimationInterface.h"

void UAnimNotify_GMAttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		ISukGMAnimationInterface* GMAniInterface = Cast<ISukGMAnimationInterface>(MeshComp->GetOwner());
		if (GMAniInterface)
		{
			GMAniInterface->AttackHitCheck();
		}
	}
}
