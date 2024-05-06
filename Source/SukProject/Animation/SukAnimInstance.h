// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SukAnimInstance.generated.h"


class ASukCharacterPlayer;
/**
 * 
 */
UCLASS()
class SUKPROJECT_API USukAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	USukAnimInstance();

	// 초기화
	virtual void NativeInitializeAnimation() override;

	// 업데이트
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


	// AnimInstance를 들고있는 Owner
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class ACharacter> Owner;

	// Character의 MovementComponent(Velocity등의 값을 가져오기 위함)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> Movement;

	//	Character's Speed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FVector Velocity;

	// Character's Speed on Ground
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float GroundSpeed;

	// Idle 상태값
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsIdle : 1;

	// 움직이고 있는지 아닌지를 확인하기 위한 경계값
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float MovingThreshold;

	// 떨어지고 있는지 확인하기 위한 값
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsFalling : 1;

	// 점프하는 중인지 나타내는 값
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsJumping : 1;

	// 점프중인지 확인하기위한 경계값
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float JumpingThreshold;

	// 달리는 중인지 나타내는 값
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsRunning : 1;

	// 구르는 중인지 나타내는 값
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsDodging : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float SideInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float ForwardInput;

	// Weapon Section
	void PlayEquipUnequipMontage();

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* PickWeaponMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* PutBackWeaponMontage;

	// 무기를 들고있는지 나타내는 값
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsHoldingWeapon : 1;


	TObjectPtr<ASukCharacterPlayer> OwnerPlayer;
};
