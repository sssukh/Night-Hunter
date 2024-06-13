// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/SukMonsterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/SukAIController.h"
#include "Components/CapsuleComponent.h"
#include "Physics/SukPhysics.h"
#include "Interface/SukCharacterAnimInterface.h"
#include "CharacterStat/SukGroundMonsterStatComponent.h"



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
		ISukCharacterAnimInterface* CharacterAnimInterface = Cast<ISukCharacterAnimInterface>(OutHitResult.GetActor());
		if (CharacterAnimInterface)
		{
			// 공격 데미지 임의로 50 넣음
			CharacterAnimInterface->TakeDamage(50.0f);
		}
	}

#if ENABLE_DRAW_DEBUG
	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = AttRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);
#endif 
}

void ASukMonsterBase::GetDamaged(float InDamage)
{
	Stat->ApplyDamage(InDamage);
}

void ASukMonsterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadMontage();
	SetActorEnableCollision(false);

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
}







