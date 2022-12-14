

#include "LatentAction/TriggerAndWait.h"
#include "CS_Subsystem.h"

void FTriggerAndWait::UpdateOperation(FLatentResponse& Response)
{
	if (TriggerSuccess)
	{
		if (Subsystem->GetEventState(Event) == EEventState::Done)
		{
			OutExecRef = EExecState::OnFinished;
			Option = Subsystem->OptionCache;
			Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
			Subsystem->SetEventState(Event, EEventState::Registered);
			Subsystem->OptionCache = FName("NoOption");
		}
	}
	else
	{
		OutExecRef = EExecState::OnFailed;
		Option = FName("NoOption");
		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
	}
}
