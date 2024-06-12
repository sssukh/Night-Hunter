// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SukCharacterStat.h"
#include "SukGameDataManager.generated.h"

#define LEVELUPSTAT 1

DECLARE_LOG_CATEGORY_EXTERN(LogSukGameDataManager, Error, All);
/**
 * 
 */
UCLASS()
class SUKPROJECT_API USukGameDataManager : public UObject
{
	GENERATED_BODY()
	
public:
	USukGameDataManager();
	static USukGameDataManager& Get();

	// CharacterData Section
public:

	// If put level bigger than 2, get Level Up stat
	FORCEINLINE FSukCharacterStat GetCharacterStat(int32 level) const { return CharacterStatTable.IsValidIndex(level - 1) ? CharacterStatTable[level - 1] : CharacterStatTable[LEVELUPSTAT]; }

	


private:
	TArray<FSukCharacterStat> CharacterStatTable;

	// Monster Data 2개, Item Data 1개 추가 필요
};
