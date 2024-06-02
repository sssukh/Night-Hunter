// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/SukWeaponComponent.h"
#include "Player/SukCharacterPlayer.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
#include "SukProjectile.h"


USukWeaponComponent::USukWeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);

	

	Character = Cast<ASukCharacterPlayer>(GetOwner());

	
}





void USukWeaponComponent::StartFire()
{

	UE_LOG(LogTemp,Warning, TEXT("FIRE!!!"));

	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}



	//// 일반 발사는 투사체 대신 lineTrace로 맞추고 이펙트만 넣기.
	//// Try and fire a projectile
	//if (ProjectileClass != nullptr)
	//{
	//	UWorld* const World = GetWorld();
	//	if (World != nullptr)
	//	{
	//		APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	//		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	//		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	//		const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

	//		//Set Spawn Collision Handling Override
	//		FActorSpawnParameters ActorSpawnParams;
	//		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	//		// Spawn the projectile at the muzzle
	//		World->SpawnActor<ASukProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	//	}
	//}

	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}

	//// Try and play a firing animation if specified
	//if (FireAnimation != nullptr)
	//{
	//	// Get the animation object for the arms mesh
	//	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	//	if (AnimInstance != nullptr)
	//	{
	//		AnimInstance->Montage_Play(FireAnimation, 1.f);
	//	}
	//}
}

void USukWeaponComponent::EndFire()
{
}

FTransform USukWeaponComponent::GetTargetingTransform()
{
	check(Character);

	AController* Controller = Character->Controller;
	if (Controller == nullptr)
	{
		return FTransform();
	}


	double FocalDistance = 1024.0f;
	FVector FocalLoc;
	FVector CamLoc;
	FRotator CamRot;

	APlayerController* PC = Cast<APlayerController>(Controller);
	check(PC);
	PC->GetPlayerViewPoint(CamLoc, CamRot);

	FVector AimDir = CamRot.Vector().GetSafeNormal();
	FocalLoc = CamLoc + (AimDir * FocalDistance);

	const FVector WeaponLoc = GetSocketLocation("Muzzle");

	FVector FinalCamLoc = FocalLoc + (((WeaponLoc - FocalLoc) | AimDir) * AimDir);
	

	return FTransform(CamRot, FinalCamLoc);
}


