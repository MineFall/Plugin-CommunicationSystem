#pragma once

#include "Engine/DataTable.h"
#include "Option/OptionInfo.h"
#include "EventInfo.generated.h"

class UEventExecutor;

USTRUCT(BlueprintType)
struct COMMUNICATIONSYSTEM_API FEventInfo
{
	GENERATED_USTRUCT_BODY()

public:

	FEventInfo() :TriggerChance(-1), bAutoEnd(true) {}

	//Event的标签，这会作为Event的唯一识别标签
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EventInfo")
		FName EventID;

	//Event具体执行的ObjectClass
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EventInfo")
		TSubclassOf<UEventExecutor> ExecutorClass;

	//Event的可触发次数，当小于0时视为无限制
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EventInfo")
		int32 TriggerChance;

	//该事件携带的选项信息
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EventInfo")
		TArray<FOptionInfo> Option;

	//该Event是否需要等待(监听)完成
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EventInfo")
		bool bAutoEnd;


	bool operator==(const FEventInfo& Other) const
	{
		return EventID == Other.EventID;
	}

	bool operator!=(const FEventInfo& Other) const
	{
		return !(*this == Other);
	}


	bool IsValid() const
	{
		return EventID != FName(TEXT("NoTrigger")) && ExecutorClass != nullptr;
	}


	friend inline uint32 GetTypeHash(const FEventInfo& Key)
	{
		uint32 Hash = 0;

		Hash = HashCombine(Hash, GetTypeHash(Key.EventID));
		return Hash;
	}
};
