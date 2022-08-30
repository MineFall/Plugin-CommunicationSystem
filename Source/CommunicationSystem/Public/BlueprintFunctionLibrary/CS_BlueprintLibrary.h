#pragma once


#include "LatentAction/DelayLoop.h"
#include "LatentAction/TriggerAndWait.h"
#include "LatentAction/DelayOutput.h"
#include "Event/EventExecutor.h"
#include "Dialog/DialogDetail.h"
#include "Engine/DataTable.h"
#include "CS_BlueprintLibrary.generated.h"



UCLASS()
class COMMUNICATIONSYSTEM_API UCS_BlueprintLibrary :public UBlueprintFunctionLibrary
{

	GENERATED_BODY()


public:

	//延迟循环，如果要相同时间循环，将UeseSameDuration设为true，并设置Duration
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Latent, LatentInfo = "LatentAction", ExpandEnumAsExecs = "In|Out", AdvancedDisplay = "9"), Category = "CS_BlueprintFunction|LatentAction")
		static void DelayLoop(
			const UObject* WorldContextObject,
			struct FLatentActionInfo LatentAction,
			const TArray<FText>& TextArray,
			const TArray<USoundBase*>& SoundArray,
			const TArray<float>& DelayArray,
			UPARAM(ref) ELoopIn& In,
			ELoopOut& Out,
			FText& DialogText,
			USoundBase*& DialogSound,
			bool UseSameDuration,
			float Duration
		);

#if 0
	//延迟执行输出节点
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Latent, LatentInfo = "LatentAction", ExpandEnumAsExecs = "In|Out"), Category = "CS_BlueprintFunction|LatentAction")
		static void DelayOutput(
			const UObject* WorldContextObject,
			struct FLatentActionInfo LatentAction,
			UPARAM(ref) EDelayIn& In,
			EDelayOut& Out,
			UDataTable* DataTable,
			const FName& CheckRow,
			TArray<FName>& OutRow
		);

#endif

	//触发一个Event并且等待其结束
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Latent, LatentInfo = "LatentAction", ExpandEnumAsExecs = "Out"), Category = "CS_BlueprintFunction|LatentAction")
		static void TriggerAndWaitEventEnd(
			const UObject* WorldContextObject,
			struct FLatentActionInfo LatentAction,
			FName EventID,
			AActor* EventOwner,
			AActor* ExecutingCharacter,
			FName& Option,
			EExecState& Out
		);


	//提供一个全局的接口，显式的调用此接口结束一个Event
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "CS_BlueprintFunction")
		static void EndEvent(
			const UObject* WorldContextObject,
			FName EventID,
			bool& bSuccess,
			FName Option = "NoOption",
			int32 ReduceChance = -1
		);


	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsValid"), Category = "CS_BlueprintFunction")
		static bool IsEventInfoValid(const FEventInfo& EventInfo);
};
