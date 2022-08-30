// Fill out your copyright notice in the Description page of Project Settings.


#include "CS_Subsystem.h"
#include "Event/EventExecutor.h"
#include "Kismet/GameplayStatics.h"

UCS_Subsystem::UCS_Subsystem()
{

}

void UCS_Subsystem::RegistEvent(const UObject* WorldContextObject, FEventInfo EventInfo)
{
	if (!RegisteredEvent.Contains(EventInfo))
	{
		RegisteredEvent.Add(EventInfo);
		SetEventTriggerAmount(EventInfo.EventID, EventInfo.TriggerChance, true);
		SetEventState(EventInfo.EventID, EEventState::Registered);
		EventInfo.ExecutorClass.GetDefaultObject()->OnEventRegistered(WorldContextObject, EventInfo.EventID);
	}
}

void UCS_Subsystem::TriggerEvent(const UObject* WorldContextObject, FName EventID, AActor* EventOwner, AActor* ExecutingCharacter, bool& bSuccess)
{
	for (const FEventInfo& Event : RegisteredEvent)
	{
		if (Event.EventID == EventID && GetEventState(EventID) == EEventState::Registered && GetEventTriggerAmount(EventID) != 0)
		{
			TArray<FOptionInfo> SortedOption;

			//将Option的Condition先检查一遍，清除未满足条件的Option，再传输给后续执行
			for (const FOptionInfo& Option : Event.Option)
			{
				//如果没有设置Condition则默认显示Option，设置了Condition则需要Condition为true的时候才显示Option
				if (!IsValid(Option.Condition) || (IsValid(Option.Condition) && Option.Condition.GetDefaultObject()->CheckCondition(WorldContextObject, EventOwner, ExecutingCharacter)))
				{
					SortedOption.Add(Option);
				}
			}

			//过滤完后，交给EventObject去执行
			if (Event.ExecutorClass)
			{
				Event.ExecutorClass.GetDefaultObject()->OnEventTrigger(WorldContextObject, EventOwner, ExecutingCharacter, EventID, SortedOption);
			}
			SetEventState(EventID, EEventState::Excuting);


			//如果为AutoEnd，那么直接设置为Done，但如果有Option信息，则必定会等待Event
			if (IsEventAutoEnd(Event.EventID) && !(Event.Option.Num() > 0))
			{
				if (GetEventTriggerAmount(EventID) > 0)
				{
					SetEventTriggerAmount(EventID);
				}
				Event.ExecutorClass.GetDefaultObject()->OnEventEnd(WorldContextObject);

				//将Event的状态设置为Done，等待下一帧LatentAction执行
				SetEventState(EventID, EEventState::Done);
			}

			bSuccess = true;
			return;

		}
	};
	bSuccess = false;
}

void UCS_Subsystem::EndEvent(const UObject* WorldContextObject, FName EventID, bool& bSuccess, FName Option, int32 ReduceChance)
{

	for (const FEventInfo& Event : RegisteredEvent)
	{
		if (Event.EventID == EventID && GetEventState(Event.EventID) == EEventState::Excuting)
		{
			if (GetEventTriggerAmount(EventID) > 0)
			{
				SetEventTriggerAmount(EventID, ReduceChance);
			}
			OptionCache = Option;

			if (Event.ExecutorClass)
			{
				Event.ExecutorClass.GetDefaultObject()->OnEventEnd(WorldContextObject);
			}

			//将Event的状态设置为Done，等待下一帧LatentAction执行
			SetEventState(EventID, EEventState::Done);
			bSuccess = true;
			return;
		}
	}
	bSuccess = false;
}

bool UCS_Subsystem::IsEventRigistered(FName EventID) const
{
	for (auto Event : RegisteredEvent)
	{
		if (Event.EventID == EventID)
			return true;
	}
	return false;
}

EEventState UCS_Subsystem::GetEventState(FName EventID)
{
	return *AllEventState.Find(EventID);
}

void UCS_Subsystem::SetEventState(FName EventID, EEventState State)
{
	EEventState& EventState = AllEventState.FindOrAdd(EventID);
	EventState = State;
}

int32 UCS_Subsystem::GetEventTriggerAmount(FName EventID)
{
	return *TriggerAmount.Find(EventID);
}

void UCS_Subsystem::SetEventTriggerAmount(FName EventID, int32 Amount, bool bOverride)
{
	int32& Chance = TriggerAmount.FindOrAdd(EventID);
	if (bOverride)
	{
		Chance = Amount;
	}
	else
	{
		Chance += Amount;
	}

	for (const FEventInfo& Event : RegisteredEvent)
	{
		if (Event.EventID == EventID)
		{
			//限定不能超过预先设置的可触发次数
			if (Chance > Event.TriggerChance)
			{
				Chance = Event.TriggerChance;
			}
			break;
		}
	}
}

bool UCS_Subsystem::IsEventAutoEnd(FName EventID) const
{
	for (auto Event : RegisteredEvent)
	{
		if (Event.EventID == EventID)
		{
			return Event.bAutoEnd;
		}
	}
	return true;
}
