#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SukCharacterStat.generated.h"

USTRUCT(BlueprintType)
struct FSukCharacterStat : public FTableRowBase
{
	GENERATED_BODY()
public:

	FSukCharacterStat() : MaxHp(0.0f), AttDamage(0.0f), AttSpeed(0.0f), AttRange(0.0f), MovementSpeed(0.0f), Jump(0.0f), CritRate(0.0f), CritDamage(0.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Jump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float CritRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float CritDamage;

	FSukCharacterStat operator+(const FSukCharacterStat& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FSukCharacterStat Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);
		int32 StatNum = sizeof(FSukCharacterStat) / sizeof(float);
		for (int32 i = 0; i < StatNum; ++i)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}

		return Result;
	}
};