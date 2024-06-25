// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/SukMonsterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/SukAIController.h"
#include "Components/CapsuleComponent.h"
#include "Physics/SukPhysics.h"
#include "CharacterStat/SukGroundMonsterStatComponent.h"
#include "Engine/DamageEvents.h"
#include "Interface/SukCharacterExpInterface.h"
#include "UI/SukWidgetComponent.h"
#include "UI/SukHpWidget.h"
#include "Components/CanvasPanel.h"
#include "UI/SukMonsterCanvasWidget.h"




// Sets default values
ASukMonsterBase::ASukMonsterBase()
{
	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;

	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_SUKCAPSULE);
	SetActorEnableCollision(false);


	AIControllerClass = ASukAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Stat = CreateDefaultSubobject<USukGroundMonsterStatComponent>(TEXT("Stat"));

	AttackRange = 100.0f;
	Hp = 100;

	// Widget Component
	HpBar = CreateDefaultSubobject<USukWidgetComponent>(TEXT("HpBar"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 3.0f));
	static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWidgetRef(TEXT("/Game/UI/WBP_MonsterHp.WBP_MonsterHp_C"));
	if (HpBarWidgetRef.Class)
	{
		HpBar->SetWidgetClass(HpBarWidgetRef.Class);
		HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		HpBar->SetDrawSize(FVector2D(150.0f, 15.0f));
		HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	HpBar->SetHiddenInGame(true);



	HitDamageCanvasWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HitDamageWidget"));
	HitDamageCanvasWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 2.0f));
	HitDamageCanvasWidget->SetupAttachment(GetMesh());
	static ConstructorHelpers::FClassFinder<UUserWidget> HitDamageWidgetRef(TEXT("/Game/UI/WBP_MonsterCanvas.WBP_MonsterCanvas_C"));
	if (HitDamageWidgetRef.Class)
	{
		HitDamageCanvasWidget->SetWidgetClass(HitDamageWidgetRef.Class);
		HitDamageCanvasWidget->SetWidgetSpace(EWidgetSpace::Screen);
		HitDamageCanvasWidget->SetDrawSize(FVector2D(300.0f, 300.0f));
		HitDamageCanvasWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}

void ASukMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	Spawn();
	Stat->OnMonsterHpZero.AddUObject(this, &ASukMonsterBase::SetDead);
}

float ASukMonsterBase::GetAIPatrolRadius()
{
	return 0.0f;
}

float ASukMonsterBase::GetAIAttackRange()
{
	return AttackRange + GetCapsuleComponent()->GetScaledCapsuleRadius();
}

float ASukMonsterBase::GetAITurnSpeed()
{
	return 5.0f;
}

void ASukMonsterBase::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void ASukMonsterBase::AttackByAI()
{

	// 몬스터 공격 진행

	// 공격 몽타주 진행
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(AttackMontage);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ASukMonsterBase::AttackEnd);

	AnimInstance->Montage_SetEndDelegate(EndDelegate, AttackMontage);


	UE_LOG(LogTemp, Warning, TEXT("Monster Attack"));
}

void ASukMonsterBase::AttackEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	OnAttackFinished.ExecuteIfBound();
}


void ASukMonsterBase::AttackHitCheck()
{
	// 몽타주에 animNotify로 연결

	// 충돌 검사
	FHitResult OutHitResult;

	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const float AttRange = this->AttackRange;
	const float AttRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
	const float AttDamage = this->AttackDamage;

	const FVector Start = GetActorLocation() + GetCapsuleComponent()->GetScaledCapsuleRadius() * GetActorForwardVector();
	const FVector End = Start + GetActorForwardVector() * AttRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, CCHANNEL_SUKACTION, FCollisionShape::MakeSphere(AttRadius), Params);
	if (HitDetected)
	{
		//ISukCharacterAnimInterface* CharacterAnimInterface = Cast<ISukCharacterAnimInterface>(OutHitResult.GetActor());
		//if (CharacterAnimInterface)
		//{
		//	// 공격 데미지 임의로 50 넣음
		//	CharacterAnimInterface->TakeDamage(50.0f);
		//}

		FDamageEvent DamageEvent;
		OutHitResult.GetActor()->TakeDamage(Stat->MonsterStat.AttDamage, DamageEvent,GetController(),this);
	}

#if ENABLE_DRAW_DEBUG
	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = AttRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);
#endif 
}



float ASukMonsterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	AnimInstance->Montage_Play(HitMontage,2.0f);

	Stat->ApplyDamage(Damage);

	CreateDamageWidget(Damage);

	return Damage;
}

void ASukMonsterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadMontage();
	SetActorEnableCollision(false);

	HpBar->SetHiddenInGame(true);

	ASukAIController* AIController = Cast<ASukAIController>(GetController());
	if (AIController)
	{
		AIController->StopAI();
	}

	// 설정한 시간 이후에 Destory
	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);

	if (nullptr != LastHitBy)
	{
		// CharacterDamageInterface 새로 정의해서 LastHitBy를 받아오자.
		ISukCharacterExpInterface* CharacterExp = Cast<ISukCharacterExpInterface>(LastHitBy->GetPawn());
		CharacterExp->GetExp(Stat->MonsterStat.Exp);
	}
}

void ASukMonsterBase::PlayDeadMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->StopAllMontages(0.0f);
		AnimInstance->Montage_Play(DeadMontage);
	}
}

void ASukMonsterBase::Spawn()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlaySpawnMontage();
}

void ASukMonsterBase::PlaySpawnMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->StopAllMontages(0.0f);
		AnimInstance->Montage_Play(SpawnMontage);

		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &ASukMonsterBase::SetSpawnedMonster);

		AnimInstance->Montage_SetEndDelegate(EndDelegate, SpawnMontage);
	}
}

void ASukMonsterBase::SetSpawnedMonster(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	SetActorEnableCollision(true);
	HpBar->SetHiddenInGame(false);
}

void ASukMonsterBase::SetupHpBarWidget(USukUserWidget* InUserWidget)
{
	USukHpWidget* HpBarWidget = Cast<USukHpWidget>(InUserWidget);
	if (HpBarWidget)
	{
		HpBarWidget->SetMaxHp(Stat->GetMaxHp());
		HpBarWidget->UpdateHpBar(Stat->GetCurrentHp(),Stat->GetMaxHp());
		Stat->OnMonsterHpChange.AddUObject(HpBarWidget, &USukHpWidget::UpdateHpBar);
	}
}

void ASukMonsterBase::CreateDamageWidget(float InDamage)
{
	K2_CreateDamageWidget(InDamage);
}









