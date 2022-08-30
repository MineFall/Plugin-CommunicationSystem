
#include "LatentAction/DelayLoop.h"

void FDelayLoop::UpdateOperation(FLatentResponse& Response)
{
	TimeRemaining -= Response.ElapsedTime();
	//如果文本数组或延迟数组为空，又或者两个数组的成员数量不一致，则立刻视为循环结束
	if (TextArray.IsEmpty() || Duration.IsEmpty() || TextArray.Num() != Duration.Num())
	{
		OutExecRef = ELoopOut::Finished;
		Text = FText();
		Sound = nullptr;
		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
	}
	else
	{
		if (Index == 0)
		{
			//该循环必须以DoLoop开始，如果从SpeedUp进来则视为无效，也不会触发任何事情
			if (InExecRef == ELoopIn::SpeedUp)
			{
				Response.DoneIf(true);
			}
			else
			{
				OutExecRef = ELoopOut::Loop;
				DoTrriger(Response);
			}
		}
		else
		{
			if (InExecRef == ELoopIn::Begin && TimeRemaining <= 0 && Index < TextArray.Num())
			{
				OutExecRef = ELoopOut::Loop;
				DoTrriger(Response);
			}
			else if (InExecRef == ELoopIn::SpeedUp && Index < TextArray.Num())
			{
				OutExecRef = ELoopOut::Loop;
				DoTrriger(Response);
				InExecRef = ELoopIn::Begin;
			}
			else if (((InExecRef == ELoopIn::Begin && TimeRemaining <= 0) || InExecRef == ELoopIn::SpeedUp) && Index >= TextArray.Num())
			{
				OutExecRef = ELoopOut::Finished;
				Index = 0;
				Text = FText();
				Sound = nullptr;
				Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
			}
		}
	}
}

void FDelayLoop::DoTrriger(FLatentResponse& Response)
{
	Text = TextArray[Index];
	Sound = SoundArray[Index];
	Response.TriggerLink(ExecutionFunction, OutputLink, CallbackTarget);
	if (bSameDuration)
	{
		TimeRemaining = TotalTime;
	}
	else
	{
		TimeRemaining = Duration[Index];
	}
	Index++;
}
