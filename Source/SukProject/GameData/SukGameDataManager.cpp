// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/SukGameDataManager.h"

USukGameDataManager::USukGameDataManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Script/Engine.DataTable'/Game/GameData/DT_CharacterStat.DT_CharacterStat'"));
	if (nullptr != DataTableRef.Object)
	{
		const UDataTable* DataTable = DataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, CharacterStatTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FSukCharacterStat*>(Value);
			}
		);
	}
	ensure(CharacterStatTable.Num() > 0);
}

USukGameDataManager& USukGameDataManager::Get()
{
	// TODO: insert return statement here
}
