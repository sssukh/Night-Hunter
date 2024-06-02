// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SukWeaponComponent.h"
#include "SukWeaponComponent_Pistol.generated.h"

/**
 * 
 */
UCLASS()
class SUKPROJECT_API USukWeaponComponent_Pistol : public USukWeaponComponent
{
	GENERATED_BODY()
public:
	USukWeaponComponent_Pistol();

	virtual void StartFire() override;
	virtual void EndFire() override;

	void FireWithLineTrace();

	UPROPERTY(EditAnywhere, Category = Weapon)
	EFireType FireType;

private:
	FTimerHandle FireTimerHandle;
};
