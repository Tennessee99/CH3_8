// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SpartaGameMode.generated.h"


/**
 * 
 */
UCLASS()
class VODPROJECT_API ASpartaGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ASpartaGameMode();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


private:
	void HandleMainTimerElapsed();

	void SpawnItemsForCurrentStage();

private:
	FTimerHandle MainTimerHandle;

	int32 AccumulatedSeconds;

	int32 MaxPlayTime;

	int32 CurrentStage;


};
