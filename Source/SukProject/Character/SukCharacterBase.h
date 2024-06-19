// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/SukCharacterExpInterface.h"
#include "Interface/SukCharacterHUDInterface.h"
#include "SukCharacterBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FShotHit);

class USukCharacterControlData;
class UAnimMontage;
class USukCharacterStatComponent;
class UWidgetComponent;
class USukHUDWidget;

UENUM()
enum class ECharacterControlType : uint8
{
	Default,
	HoldingWeapon
};

UCLASS()
class SUKPROJECT_API ASukCharacterBase : public ACharacter, public ISukCharacterExpInterface, public ISukCharacterHUDInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASukCharacterBase();

	virtual void BeginPlay() override;

	// Dead Section
	virtual void SetDead();
	void PlayDeadAnimation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> DeadMontage;
	
	float DeadEventDelayTime = 5.0f;

	// interaction
public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void GetExp(float InExp) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USukCharacterStatComponent> Stat;


	// UI section
public:
	virtual void SetupCharacterHpBar(USukHUDWidget* InHUDWidget) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> HpBar;

	FShotHit ShotHit;

	virtual void ShotHit();
};
