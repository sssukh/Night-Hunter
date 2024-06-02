// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SukCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SukCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "Animation/AnimMontage.h"
#include "Character/SukCharacterControlData.h"
#include "Engine/LocalPlayer.h"

#include "Animation/SukAnimInstance.h"
#include "Weapon/SukWeaponComponent.h"




ASukCharacterPlayer::ASukCharacterPlayer()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 70.0f);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;


	IsRunning = false;

	IsDodging = false;

	// Weapon
	Weapon = CreateDefaultSubobject<USukWeaponComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));

	bIsHoldingWeapon = false;

	CurrentCharacterControlType = ECharacterControlType::Default;
}

void ASukCharacterPlayer::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ASukCharacterPlayer::ChangeCharacterControl()
{
	if (CurrentCharacterControlType == ECharacterControlType::Default)
	{
		SetCharacterControl(ECharacterControlType::HoldingWeapon);
	}
	else if (CurrentCharacterControlType == ECharacterControlType::HoldingWeapon)
	{
		SetCharacterControl(ECharacterControlType::Default);
	}
}

void ASukCharacterPlayer::SetCharacterControl(ECharacterControlType NewCharacterControlType)
{
	USukCharacterControlData* NewCharacterControl = CharacterControlManager[NewCharacterControlType];
	check(NewCharacterControl);

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());

	SetCharacterControlData(NewCharacterControl);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		UInputMappingContext* NewMappingContext = NewCharacterControl->InputMappingContext;
		if (NewMappingContext)
		{
			Subsystem->AddMappingContext(NewMappingContext, 0);
		}
	}

	CurrentCharacterControlType = NewCharacterControlType;
}

void ASukCharacterPlayer::SetCharacterControlData(const USukCharacterControlData* CharacterControlData)
{
	USukAnimInstance* AnimInstance = Cast<USukAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->PlayEquipUnequipMontage();

	bIsHoldingWeapon = CharacterControlData->bIsHoldingWeapon;
}


void ASukCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASukCharacterPlayer::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ASukCharacterPlayer::EndMove);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASukCharacterPlayer::Look);

		//Runing
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &ASukCharacterPlayer::Run);

		//Dodging
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ASukCharacterPlayer::Dodge);

		//Weapon
		EnhancedInputComponent->BindAction(EquipWeaponAction, ETriggerEvent::Triggered, this, &ASukCharacterPlayer::ChangeCharacterControl);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ASukCharacterPlayer::StartFire);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &ASukCharacterPlayer::EndFire);


	}

}

void ASukCharacterPlayer::Move(const FInputActionValue& Value)
{
	

	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);

	SideInput = MovementVector.Y;
	ForwardInput = MovementVector.X;

	
}

void ASukCharacterPlayer::EndMove()
{
	SideInput = 0.0f;
	ForwardInput = 0.0f;
}

void ASukCharacterPlayer::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASukCharacterPlayer::Run()
{
	IsRunning = !IsRunning;
}

void ASukCharacterPlayer::Dodge()
{
	// 점프상태 일때 return하는 조건 추가하기
	if (IsDodging||(SideInput==0&&ForwardInput==0))
		return;

	IsDodging = true;

	

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	

	UAnimMontage* CurrentMontage;

	if (ForwardInput != 0.0f)
	{
		if (ForwardInput > 0)
		{
			CurrentMontage = DodgeMontage[0];
		}
		else
		{
			CurrentMontage = DodgeMontage[1];
		}
	}
	else
	{
		if (SideInput > 0)
		{
			CurrentMontage = DodgeMontage[2];
		}
		else
		{
			CurrentMontage = DodgeMontage[3];
		}
	}
	AnimInstance->Montage_Play(CurrentMontage, 1.0f);

	FOnMontageEnded EndDodgeMontage;
	EndDodgeMontage.BindUObject(this, &ASukCharacterPlayer::DodgeEnd);

	AnimInstance->Montage_SetEndDelegate(EndDodgeMontage, CurrentMontage);

}

void ASukCharacterPlayer::DodgeEnd(UAnimMontage* InDodgeMontage, bool bInterrupted)
{
	IsDodging = false;


}

void ASukCharacterPlayer::EquipWeapon()
{
	bIsHoldingWeapon = !bIsHoldingWeapon;
}

void ASukCharacterPlayer::StartFire()
{
	if (Weapon)
	{
		Weapon->StartFire();
	}
}

void ASukCharacterPlayer::EndFire()
{
	if (Weapon)
	{
		Weapon->EndFire();
	}
}

void ASukCharacterPlayer::FireHitCheck()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);


}




