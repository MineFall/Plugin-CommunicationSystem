
#include "CommunicationSystem.h"
#include "BlueprintFunctionLibrary/CS_BlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "CS_Subsystem.h"


void UCS_BlueprintLibrary::DelayLoop(const UObject* WorldContextObject, FLatentActionInfo LatentAction, const TArray<FText>& TextArray, const TArray<USoundBase*>& SoundArray, const TArray<float>& DelayArray, UPARAM(ref) ELoopIn& In, ELoopOut& Out, FText& DialogText, USoundBase*& DialogSound, bool UseSameDuration, float Duration)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	if (World)
	{
		FLatentActionManager& Manager = World->GetLatentActionManager();
		if (Manager.FindExistingAction<FDelayLoop>(LatentAction.CallbackTarget, LatentAction.UUID) == NULL)
		{
			Manager.AddNewAction(LatentAction.CallbackTarget, LatentAction.UUID, new FDelayLoop(LatentAction, Duration, UseSameDuration, In, Out, TextArray, SoundArray, DelayArray, DialogText, DialogSound));
		}
	}
	else
	{
		UE_LOG(LogCommunicationSystem, Warning, TEXT("BlueprintFunction Warning : DelayLoop Get nullptr World"));
	}
}

#if 0
void UCS_BlueprintLibrary::DelayOutput(const UObject* WorldContextObject, FLatentActionInfo LatentAction, UPARAM(ref) EDelayIn& In, EDelayOut& Out, UDataTable* DataTable, const FName& CheckRow, TArray<FName>& OutRow)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	if (World)
	{
		FDialogDetail* Dialog = DataTable->FindRow<FDialogDetail>(CheckRow, FString::Printf(TEXT("DelayOutput")));
		float Time = 0;

		//如果找到了Row，则取Row提供的数据，否则延迟时间默认为0
		if (Dialog)
		{
			Time = Dialog->During;
		}

		FLatentActionManager& Manager = World->GetLatentActionManager();
		if (Manager.FindExistingAction<FDelayOutput>(LatentAction.CallbackTarget, LatentAction.UUID) == NULL)
		{
			Manager.AddNewAction(LatentAction.CallbackTarget, LatentAction.UUID, new FDelayOutput(LatentAction, Time, In, Out));
		}
	}
	else
	{
		UE_LOG(LogCommunicationSystem, Warning, TEXT("BlueprintFunction Warning : DelayOutput Get nullptr World"));
	}
}

#endif

void UCS_BlueprintLibrary::TriggerAndWaitEventEnd(const UObject* WorldContextObject, FLatentActionInfo LatentAction, FName EventID, AActor* EventOwner, AActor* ExecutingCharacter, FName& OptionRow, EExecState& Out)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	UCS_Subsystem* Subsystem = nullptr;
	bool bSuccess = false;
	if (GameInstance)
	{
		Subsystem = GameInstance->GetSubsystem<UCS_Subsystem>();
		Subsystem->TriggerEvent(WorldContextObject, EventID, EventOwner, ExecutingCharacter, bSuccess);


		//注册Latent时间等待Event结束
		UWorld* World = GameInstance->GetWorld();
		FLatentActionManager& Manager = World->GetLatentActionManager();
		if (Manager.FindExistingAction<FTriggerAndWait>(LatentAction.CallbackTarget, LatentAction.UUID) == NULL)
		{
			Manager.AddNewAction(LatentAction.CallbackTarget, LatentAction.UUID, new FTriggerAndWait(LatentAction, EventID, Out, Subsystem, bSuccess, OptionRow));
		}

	};
}


void UCS_BlueprintLibrary::EndEvent(const UObject* WorldContextObject, FName EventID, bool& bSuccess, FName Option, int32 ReduceChance)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	UCS_Subsystem* Subsystem = nullptr;
	if (GameInstance)
	{
		Subsystem = GameInstance->GetSubsystem<UCS_Subsystem>();
		Subsystem->EndEvent(WorldContextObject, EventID, bSuccess, Option, ReduceChance);
	}
}

bool UCS_BlueprintLibrary::IsEventInfoValid(const FEventInfo& EventInfo)
{
	return EventInfo.IsValid();
}
