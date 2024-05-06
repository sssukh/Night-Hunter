// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SukCharacterBase.generated.h"

class USukCharacterControlData;

UENUM()
enum class ECharacterControlType : uint8
{
	Default,
	HoldingWeapon
};

UCLASS()
class SUKPROJECT_API ASukCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASukCharacterBase();

	




};
