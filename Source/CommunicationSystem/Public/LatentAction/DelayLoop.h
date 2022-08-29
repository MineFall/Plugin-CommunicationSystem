#pragma once


#include "LatentActions.h"
#include "DelayLoop.generated.h"


UENUM()
enum class ELoopIn :uint8
{
	Begin = 0,
	SpeedUp
};

UENUM()
enum class ELoopOut :uint8
{
	Loop = 0,
	Finished
};


class COMMUNICATIONSYSTEM_API FDelayLoop :public FPendingLatentAction
{

public:
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	float TotalTime;
	float TimeRemaining;
	bool bSameDuration;
	ELoopIn& InExecRef;
	ELoopOut& OutExecRef;
	const TArray<FText>& TextArray;
	const TArray<USoundBase*>& SoundArray;
	const TArray<float>& Duration;
	FText& Text;
	USoundBase*& Sound;
	int32 Index;


	FDelayLoop(const FLatentActionInfo& LatentInfo, float Duration, bool UseSameDuration, ELoopIn& InExc, ELoopOut& OutExc, const TArray<FText>& InTextArray, const TArray<USoundBase*>& InSoundArray, const TArray<float>& DelayArray, FText& OutText, USoundBase*& OutSound)
		:ExecutionFunction(LatentInfo.ExecutionFunction), OutputLink(LatentInfo.Linkage),
		CallbackTarget(LatentInfo.CallbackTarget), TotalTime(Duration), TimeRemaining(Duration), bSameDuration(UseSameDuration),
		InExecRef(InExc), OutExecRef(OutExc), TextArray(InTextArray), SoundArray(InSoundArray), Duration(DelayArray), Text(OutText), Sound(OutSound), Index(0)
	{

	}

	virtual void UpdateOperation(FLatentResponse& Response) override;

	void DoTrriger(FLatentResponse& Response);
};
