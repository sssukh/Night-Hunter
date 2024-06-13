#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SukCharacterExp.generated.h"

USTRUCT(BlueprintType)
struct FSukCharacterExp : public FTableRowBase
{
	GENERATED_BODY()
public:

	FSukCharacterExp() : ExpMax(0.0f), ExpIncreaseRate(0.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float ExpMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float ExpIncreaseRate;



	FSukCharacterExp operator+(const FSukCharacterExp& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FSukCharacterExp Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);
		int32 StatNum = sizeof(FSukCharacterExp) / sizeof(float);
		for (int32 i = 0; i < StatNum; ++i)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}

		return Result;
	}
};