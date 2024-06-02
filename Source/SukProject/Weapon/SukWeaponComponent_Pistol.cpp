// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/SukWeaponComponent_Pistol.h"
#include "Player/SukCharacterPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Interface/SukMonsterInterface.h"
#include "Physics/SukPhysics.h"



USukWeaponComponent_Pistol::USukWeaponComponent_Pistol()
{
	FireType = EFireType::LineTrace;

	AttackRange = 2000.0f;
	FireInterval = 0.5f;
}

void USukWeaponComponent_Pistol::StartFire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}


	if (FireType == EFireType::LineTrace)
	{
		if(!GetWorld()->GetTimerManager().IsTimerActive(FireTimerHandle))
			GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &USukWeaponComponent_Pistol::FireWithLineTrace, FireInterval, true,0.0f);
	}


	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
}

void USukWeaponComponent_Pistol::EndFire()
{
	if (FireTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
	}
}

void USukWeaponComponent_Pistol::FireWithLineTrace()
{
	FHitResult OutHitResult;

	const FVector Start = GetTargetingTransform().GetTranslation();

	const FVector End = (Character->GetControlRotation().Vector() * AttackRange) + Start;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Character);

	bool HitDetected = GetWorld()->LineTraceSingleByChannel(OutHitResult, Start, End, CCHANNEL_SUKACTION, CollisionParams);

	if (HitDetected)
	{
		ISukMonsterInterface* MonsterInterface = Cast<ISukMonsterInterface>(OutHitResult.GetActor());
		if (MonsterInterface == nullptr)
		{
			return;
		}

		MonsterInterface->GetDamaged(AttackDamage);
	}

#if ENABLE_DRAW_DEBUG
	FColor HitColor = HitDetected ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), Start, End, HitColor, false,10.0f);

#endif

	if (OutHitResult.GetActor())
	{
		AActor* hitActor = OutHitResult.GetActor();
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Hit Actor Name: %s"), *hitActor->GetName()));
	}


	if (CharacterFireAnimation != nullptr)
	{
		UAnimInstance* CharacterAnimInstance = Character->GetMesh()->GetAnimInstance();
		if (CharacterAnimInstance != nullptr)
		{
			CharacterAnimInstance->Montage_Play(CharacterFireAnimation, 1.0f);
		}
	}

}



