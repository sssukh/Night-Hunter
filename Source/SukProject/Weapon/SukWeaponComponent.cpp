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

	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (Owner == nullptr)
	{
		return FTransform();
	}
	const FVector WeaponLoc = Owner->GetMesh()->GetSocketLocation("handslot_rSocket");

	FVector FinalCamLoc = FocalLoc + (((WeaponLoc - FocalLoc) | AimDir) * AimDir);
	

	return FTransform(CamRot, FinalCamLoc);
}


