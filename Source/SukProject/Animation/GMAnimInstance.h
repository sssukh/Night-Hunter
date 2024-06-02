// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GMAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SUKPROJECT_API UGMAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UGMAnimInstance();
	
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
};
