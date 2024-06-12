// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/SukGameDataManager.h"

DEFINE_LOG_CATEGORY(LogSukGameDataManager);

USukGameDataManager::USukGameDataManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Script/Engine.DataTable'/Game/GameData/DT_CharacterStat.DT_CharacterStat'"));
	if (nullptr != DataTableRef.Object)
	{
		const UDataTable* DataTable = DataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<FSukCharacterStat*> arr;
		DataTable->GetAllRows<FSukCharacterStat>(TEXT("GetAllRows"), arr);

		for (int i = 0; i < arr.Num(); ++i)
		{
			CharacterStatTable.Add(*arr[i]);
		}

		for (int i = 0; i < CharacterStatTable.Num(); ++i)
		{
			UE_LOG(LogSukGameDataManager, Error, TEXT("Row %d : Attack Damage : %f, Attack Range : %f"), i,CharacterStatTable[i].AttDamage, CharacterStatTable[i].AttRange);
		}

	}
}

USukGameDataManager& USukGameDataManager::Get()
{
	USukGameDataManager* Singleton = CastChecked<USukGameDataManager>(GEngine->GameSingleton);
	if (Singleton)
	{
		return *Singleton;
	}

	UE_LOG(LogSukGameDataManager, Error, TEXT("Invalid Game Singleton"));

	return *NewObject<USukGameDataManager>();
}
