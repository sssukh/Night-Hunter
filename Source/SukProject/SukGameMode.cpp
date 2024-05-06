// Fill out your copyright notice in the Description page of Project Settings.


#include "SukGameMode.h"
#include "Player/SukCharacterPlayer.h"

ASukGameMode::ASukGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> ThirdPersonClassRef(TEXT("/Game/Blueprints/BP_SukCharacterPlayer.BP_SukCharacterPlayer_C"));
	if (ThirdPersonClassRef.Class)
	{
		DefaultPawnClass = ThirdPersonClassRef.Class;
	}
	
}
