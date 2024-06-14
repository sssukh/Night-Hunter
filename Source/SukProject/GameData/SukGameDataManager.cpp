// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/SukGameDataManager.h"

DEFINE_LOG_CATEGORY(LogSukGameDataManager);

USukGameDataManager::USukGameDataManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Script/Engine.DataTable'/Game/GameData/SukCharacterStat.SukCharacterStat'"));
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

	}

	static ConstructorHelpers::FObjectFinder<UDataTable> GMDataTableRef(TEXT("/Script/Engine.DataTable'/Game/GameData/SukGroundMonsterStat.SukGroundMonsterStat'"));
	if (nullptr != GMDataTableRef.Object)
	{
		const UDataTable* GMDataTable = GMDataTableRef.Object;
		check(GMDataTable->GetRowMap().Num() > 0);

		TArray<FSukGroundMonsterStat*> arr;
		GMDataTable->GetAllRows<FSukGroundMonsterStat>(TEXT("GetAllGMRows"), arr);

		for (int i = 0; i < arr.Num(); ++i)
		{
			GroundMonsterStatTable.Add(*arr[i]);
		}
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> CEDataTableRef(TEXT("/Script/Engine.DataTable'/Game/GameData/SukCharacterExp.SukCharacterExp'"));
	if (nullptr != CEDataTableRef.Object)
	{
		const UDataTable* CEDataTable = CEDataTableRef.Object;
		check(CEDataTable->GetRowMap().Num() > 0);

		TArray<FSukCharacterExp*> arr;
		CEDataTable->GetAllRows<FSukCharacterExp>(TEXT("GetAllGMRows"), arr);

		
		CharacterExpTable = *arr[0];
		
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
