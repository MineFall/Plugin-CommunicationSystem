#pragma once

#include "LatentActions.h"
#include "DelayOutput.generated.h"

UENUM()
enum class EDelayIn :uint8
{
	Begin = 0,
	SpeedUp
};


UENUM()
enum class EDelayOut :uint8
{
	OnFinished = 0,
	OnInterrupt,
	OnEvent
};



class COMMUNICATIONSYSTEM_API FDelayOutput :public FPendingLatentAction
{
public:

	FName ExecutionFunction;
	int32 OutLinkage;
	FWeakObjectPtr CallbackTarget;
	float DelayTime;
	EDelayIn& InExec;
	EDelayOut& OutExec;

	FDelayOutput(const FLatentActionInfo& LatentInfo, float During, EDelayIn& In, EDelayOut& Out) :ExecutionFunction(LatentInfo.ExecutionFunction),
		OutLinkage(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget), DelayTime(During),
		InExec(In), OutExec(Out)
	{

	}

};
