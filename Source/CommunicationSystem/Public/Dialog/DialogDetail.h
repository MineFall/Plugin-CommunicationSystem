#pragma once

#include "Engine/DataTable.h"
#include "Event/EventInfo.h"
#include "DialogDetail.generated.h"


USTRUCT(BlueprintType)
struct COMMUNICATIONSYSTEM_API FDialogDetail :public FTableRowBase
{

	GENERATED_USTRUCT_BODY()

public:

	FDialogDetail() :
		During(3),
		TriggerEvent("NoTrigger")
	{}

	//对话文本
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialogDetail")
		FText DialogText;

	//对话的语音，如果有语音那么以"语音的总播放时长"为准，下面的During将被无视
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialogDetail")
		USoundBase* Sound;

	//对话的持续时长
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialogDetail")
		float During;

	//该句对白会注册的Event
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialogDetail")
		FEventInfo RegistEvent;

	//该句对白会触发的Event(必须先注册Event，才能触发)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialogDetail")
		FName TriggerEvent;

	//下一句对白对应的DataTable的Row(如果TriggerEvent里带有Option，那么此项将被无视)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialogDetail")
		FString NextDialog;
};
