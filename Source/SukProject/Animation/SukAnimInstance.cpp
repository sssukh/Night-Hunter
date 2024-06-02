// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SukAnimInstance.h"
#include "GameFramework/Character.h"
#include "Player/SukCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

USukAnimInstance::USukAnimInstance()
{
	MovingThreshold = 3.0f;
	JumpingThreshold = 50.0f;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PickWeaponMontageFinder(TEXT("/Game/Animations/AnimationMontage/AM_GrabWeaponFromBehind.AM_GrabWeaponFromBehind"));
	if (PickWeaponMontageFinder.Object)
	{
		PickWeaponMontage = PickWeaponMontageFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PutBackWeaponMontageFinder(TEXT("/Game/Animations/AnimationMontage/AM_PutBackWeaponBehind.AM_PutBackWeaponBehind"));
	if (PutBackWeaponMontageFinder.Object)
	{
		PutBackWeaponMontage = PutBackWeaponMontageFinder.Object;
	}

	
}

void USukAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// Character의 Movement가져옴
	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}

	OwnerPlayer = Cast<ASukCharacterPlayer>(Owner);
}

void USukAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		// 하늘 방향(z)를 제외한 속도
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed < MovingThreshold;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshold);

		bIsRunning = OwnerPlayer->IsRunning;

		SideInput = OwnerPlayer->SideInput;
		ForwardInput = OwnerPlayer->ForwardInput;

		bIsDodging = OwnerPlayer->IsDodging;

		bIsHoldingWeapon = OwnerPlayer->bIsHoldingWeapon;
	}
}

void USukAnimInstance::PlayEquipUnequipMontage()
{
	if (!bIsHoldingWeapon)
	{
		Montage_Play(PickWeaponMontage,2.0f);
	}
	else
	{
		Montage_Play(PutBackWeaponMontage, 2.0f);
	}
}
