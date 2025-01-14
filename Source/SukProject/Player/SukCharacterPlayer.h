// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SukCharacterBase.h"
#include "InputActionValue.h"
#include "Interface/SukAnimationFireInterface.h"
#include "SukCharacterPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputComponent;
class UInputAction;
class UAnimMontage;
class USukWeaponComponent;



/**
 * 
 */
UCLASS()
class SUKPROJECT_API ASukCharacterPlayer : public ASukCharacterBase //, public ISukAnimationFireInterface
{
	GENERATED_BODY()
public:
	ASukCharacterPlayer();


public:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

	virtual void PostInitializeComponents() override;

	//void ChangeCharacterControl();

	//void SetCharacterControl(ECharacterControlType NewCharacterControlType);

	//void SetCharacterControlData(const USukCharacterControlData* CharacterControlData);

	//ECharacterControlType CurrentCharacterControlType;

	//UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	//TMap<ECharacterControlType, USukCharacterControlData*> CharacterControlManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* WeaponMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> RunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> DodgeAction;
public:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for movement input */
	void EndMove();

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Run();

	bool IsRunning;

	void Dodge();

	void DodgeEnd(UAnimMontage* InDodgeMontage, bool bInterrupted);

	UFUNCTION(BlueprintCallable,Category = "Animation")
	FORCEINLINE void SetDodging(bool bIsDodging) { IsDodging = bIsDodging; }

	UFUNCTION(BlueprintCallable, Category = "Animation")
	FORCEINLINE void SetRunningg(bool bIsRunning) { IsRunning = bIsRunning; }

	bool IsDodging;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	float SideInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	float ForwardInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> DodgeMontage;



public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// Weapon
public:
	void SetBeginOfFight();
	void SetEndOfFight();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USukWeaponComponent> Weapon;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Weapon)
	bool bIsOnFight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> AimMontage;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> EquipWeaponAction;*/


	void StartFire();

	void EndFire();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> FireAction;

	FTimerHandle FightTimerHandle;

//	// Fire Hit Check 
//public:
//	virtual void FireHitCheck() override;
	



};



