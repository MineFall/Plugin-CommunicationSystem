// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EventExecutor.generated.h"

/**
 *
 */
UCLASS(Abstract, Blueprintable, meta = (ShowWorldContextPin))
class COMMUNICATIONSYSTEM_API UEventExecutor : public UObject
{
	GENERATED_BODY()

public:

	UEventExecutor();

	UFUNCTION(BlueprintImplementableEvent, meta = (WorldContext = "WorldContextObject"))
		void OnEventRegistered(const UObject* WorldContextObject, const FName& EventID);

	UFUNCTION(BlueprintImplementableEvent, meta = (WorldContext = "WorldContextObject"))
		void OnEventTrigger(const UObject* WorldContextObject, AActor* EventOwer, AActor* ExecutingCharacter, const FName& EventID, const TArray<FOptionInfo>& OptionInfo);

	UFUNCTION(BlueprintImplementableEvent, meta = (WorldContext = "WorldContextObject"))
		void OnEventEnd(const UObject* WorldContextObject);


};
