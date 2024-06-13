#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SukGroundMonsterStat.generated.h"

USTRUCT(BlueprintType)
struct FSukGroundMonsterStat : public FTableRowBase
{
	GENERATED_BODY()

	public:
	FSukGroundMonsterStat() : MaxHp(0.0f), AttDamage(0.0f), AttRange(0.0f), AttSpeed(0.0f), MovementSpeed(0.0f), Exp(0.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Exp;

	FSukGroundMonsterStat operator+(const FSukGroundMonsterStat& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FSukGroundMonsterStat Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);
		int32 StatNum = sizeof(FSukGroundMonsterStat) / sizeof(float);
		for (int32 i = 0; i < StatNum; i++)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}

		return Result;
	}
};