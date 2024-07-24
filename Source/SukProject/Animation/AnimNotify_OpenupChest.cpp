// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_OpenupChest.h"
#include "Prop/SukChest.h"

void UAnimNotify_OpenupChest::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		ASukChest* Chest = Cast<ASukChest>(MeshComp->GetOwner());
		if (Chest)
		{
			Chest->K2_AfterChestOpen();
		}
	}
}
