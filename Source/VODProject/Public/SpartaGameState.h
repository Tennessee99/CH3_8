// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SpartaGameState.generated.h"

/**
 *
 */
UCLASS()
class VODPROJECT_API ASpartaGameState : public AGameState
{
	GENERATED_BODY()

public:
	ASpartaGameState();

	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 SpawnedCoinCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 CollectedCoinCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	float LevelDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	int32 CurrentLevelIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	int32 MaxLevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	TArray<FName> LevelMapNames;


	FTimerHandle LevelTimerHandle;

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameOver();

	void StartLevel();
	void OnLevelTimeUp();
	void EndLevel();
	void OnCoinCollected();

};
