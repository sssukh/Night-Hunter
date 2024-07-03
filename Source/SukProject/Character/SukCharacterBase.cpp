// Fill out your copyright notice in the Description page of Project Settings.


#include "SukCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Physics/SukPhysics.h"
#include "CharacterStat/SukCharacterStatComponent.h"
#include "UI/SukWidgetComponent.h"
#include "UI/SukHUDWidget.h"
#include "Player/SukPlayerController.h"
#include "EnhancedInputComponent.h"


// Sets default values
ASukCharacterBase::ASukCharacterBase()
{
	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_SUKCAPSULE);

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 720.0f);
	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceMeshRef(TEXT("/Game/Characters/Mannequins/Animations/ABP_Quinn.ABP_Quinn_C"));
	if (AnimInstanceMeshRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceMeshRef.Class);
	}

	// Stat Component
	Stat = CreateDefaultSubobject<USukCharacterStatComponent>(TEXT("Stat"));

	// HUD와 hpBar는 어떻게 연결할까?

}

void ASukCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		EnableInput(PlayerController);
	}
	
	Stat->OnHpZero.AddUObject(this, &ASukCharacterBase::SetDead);
}

void ASukCharacterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();
	SetActorEnableCollision(false);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		DisableInput(PlayerController);
	}
}

void ASukCharacterBase::PlayDeadAnimation()
{
	UAnimInstance* AnimIns = GetMesh()->GetAnimInstance();
	AnimIns->StopAllMontages(0.0f);
	AnimIns->Montage_Play(DeadMontage);
}


float ASukCharacterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	Stat->ApplyDamage(Damage);

	return Damage;
}

void ASukCharacterBase::GetExp(float InExp)
{
	Stat->ApplyExp(InExp);
}



void ASukCharacterBase::SetupCharacterHUDWidget(USukHUDWidget* InHUDWidget)
{
	if (InHUDWidget)
	{
		InHUDWidget->UpdateHpBar(Stat->GetCurrentHp(),Stat->GetMaxHp());

		Stat->OnHpChanged.AddUObject(InHUDWidget, &USukHUDWidget::UpdateHpBar);

		ShotHitDelegate.AddUObject(InHUDWidget, &USukHUDWidget::CrosshairShowHit);
	}
}

void ASukCharacterBase::ShotHit()
{
	ShotHitDelegate.Broadcast();
}





