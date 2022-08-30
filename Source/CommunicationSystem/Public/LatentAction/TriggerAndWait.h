#pragma once

#include "LatentActions.h"
#include "TriggerAndWait.generated.h"

class UCS_Subsystem;


UENUM()
enum class EExecState :uint8
{
	OnFinished = 0,
	OnFailed
};



class COMMUNICATIONSYSTEM_API FTriggerAndWait : public FPendingLatentAction
{

public:
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	FName Event;
	EExecState& OutExecRef;
	UCS_Subsystem* Subsystem;
	bool TriggerSuccess;
	FName& Option;



	FTriggerAndWait(const FLatentActionInfo& LatentInfo, FName EventID, EExecState& Exec, UCS_Subsystem* SSystem, bool bSuccess, FName& OutOption) :
		ExecutionFunction(LatentInfo.ExecutionFunction), OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget),
		Event(EventID), OutExecRef(Exec), Subsystem(SSystem), TriggerSuccess(bSuccess), Option(OutOption)
	{

	}

	virtual void UpdateOperation(FLatentResponse& Response) override;

};
