// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/SukWeaponComponent_Pistol.h"
#include "Player/SukCharacterPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Physics/SukPhysics.h"
#include "Engine/DamageEvents.h"



USukWeaponComponent_Pistol::USukWeaponComponent_Pistol()
{
	FireType = EFireType::LineTrace;

	AttackRange = 2000.0f;
	FireInterval = 0.5f;
}

void USukWeaponComponent_Pistol::StartFire()
{
	Super::StartFire();
	if (OwnerCharacter == nullptr || OwnerCharacter->GetController() == nullptr)
	{
		return;
	}


	if (FireType == EFireType::LineTrace)
	{
		if(!GetWorld()->GetTimerManager().IsTimerActive(FireTimerHandle))
			GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &USukWeaponComponent_Pistol::FireWithLineTrace, FireInterval, true,0.0f);
	}

}

void USukWeaponComponent_Pistol::EndFire()
{
	Super::EndFire();
	if (FireTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
	}
}

void USukWeaponComponent_Pistol::FireWithLineTrace()
{
	FHitResult OutHitResult;

	const FVector Start = GetTargetingTransform().GetTranslation();

	const FVector End = (OwnerCharacter->GetControlRotation().Vector() * AttackRange) + Start;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(OwnerCharacter);

	bool HitDetected = GetWorld()->LineTraceSingleByChannel(OutHitResult, Start, End, CCHANNEL_SUKACTION, CollisionParams);

	if (HitDetected)
	{
		FDamageEvent DamageEvent;
		OutHitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetCharacterController(), GetOwnerCharacter());
		OwnerCharacter->ShotHit();
		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(OutHitResult.GetActor(), HitSound, OutHitResult.GetActor()->GetActorLocation());
		}
	}

#if ENABLE_DRAW_DEBUG
	FColor HitColor = HitDetected ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), Start, End, HitColor, false,5.0f);

#endif

	if (OutHitResult.GetActor())
	{
		AActor* hitActor = OutHitResult.GetActor();
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Hit Actor Name: %s"), *hitActor->GetName()));
	}


	if (CharacterFireAnimation != nullptr)
	{
		UAnimInstance* CharacterAnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
		if (CharacterAnimInstance != nullptr)
		{
			CharacterAnimInstance->Montage_Play(CharacterFireAnimation, 1.0f);
		}
	}

	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Start);
	}

}



