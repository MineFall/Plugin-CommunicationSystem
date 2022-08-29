// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Event/EventInfo.h"
#include "CS_Subsystem.generated.h"

/**
 *
 */

class UEventObject;


//这只是一个运行时的状态检测，不要拿它来判定Event的注册情况
UENUM()
enum class EEventState :uint8
{
	Registered = 0,
	Excuting,
	Done
};



UCLASS()
class COMMUNICATIONSYSTEM_API UCS_Subsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UCS_Subsystem();

	//注册一个Event
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "CS_Subsystem")
		void RegistEvent(const UObject* WorldContextObject, FEventInfo EventInfo);

	//触发一个已经注册的Event
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "CS_Subsystem")
		void TriggerEvent(const UObject* WorldContextObject, FName EventID, AActor* EventOwner, AActor* ExecutingCharacter, bool& bSuccess);

	//结束一个正在进行的Event
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "CS_Subsystem")
		void EndEvent(
			const UObject* WorldContextObject,
			FName EventID,
			bool& Success,
			FName Option = "NoOption",
			int32 ReduceChance = -1
		);

	//检查某个Event是否已经注册
	UFUNCTION(BlueprintPure, Category = "CS_Subsystem")
		bool IsEventRigistered(FName EventID) const;



	//获取某个Event的状态
	UFUNCTION(BlueprintPure, Category = "CS_Subsystem")
		EEventState GetEventState(FName EventID);

	//设置某个Event的状态
	void SetEventState(FName EventID, EEventState State);

	//获取Event的可触发次数
	UFUNCTION(BlueprintPure, Category = "CS_Subsystem")
		int32 GetEventTriggerAmount(FName EventID);

	//设置Event的可触发次数
	void SetEventTriggerAmount(FName EventID, int32 Amount = -1, bool bOverride = false);

	//Event是否自动End，而不需要手动End
	bool IsEventAutoEnd(FName EventID) const;


public:



protected:



	//已经注册的Event
	UPROPERTY()
		TArray<FEventInfo> RegisteredEvent;

	//所有已经注册了的Event的状态
	UPROPERTY()
		TMap<FName, EEventState> AllEventState;

	//对于注册的Event，每个Event已经触发的次数
	UPROPERTY()
		TMap<FName, int32> TriggerAmount;


public:
	//一个中转变量，用来存储玩家的Option，通常为NoOption
	FName OptionCache;
};
