// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpartaHUDWidget.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class VODPROJECT_API USpartaHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetScore(int32 InScore);

	void SetTime(int32 InTime);

	void SetHP(float InCurrentHP, float InMaxHP);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimeText;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPBar;


};
