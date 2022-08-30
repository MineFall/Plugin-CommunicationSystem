#pragma once

#include "OptionInfo.generated.h"

class UConditionCheck;

USTRUCT(BlueprintType)
struct COMMUNICATIONSYSTEM_API FOptionInfo
{
	GENERATED_USTRUCT_BODY()

public:
	FOptionInfo()
	{
		Row = FName("NoOption");
	}

	//选项的文本
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OptionInfo")
		FText OptionText;

	//此选项会跳至DataTable的哪一行
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OptionInfo")
		FName Row;

	//如果这个Option是一个有附加条件才会出现的Option，那么在这里添加条件检查
	UPROPERTY(EditDefaultsOnly, Category = "OptionInfo")
		TSubclassOf<UConditionCheck> Condition;

	//该选项被选择后，会导致Event的可触发次数变化多少，正值为增加，负值为减少
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OptionInfo")
		int32 ChanceChange;
};



UCLASS(Abstract, Blueprintable, meta = (ShowWorldContextPin))
class COMMUNICATIONSYSTEM_API UConditionCheck :public UObject
{
	GENERATED_BODY()
public:

	UConditionCheck() {};

	UFUNCTION(BlueprintImplementableEvent, meta = (WorldContext = "WorldContextObject"))
		bool CheckCondition(const UObject* WorldContextObject, AActor* EventOwner, AActor* ExecutingCharacter);
};
