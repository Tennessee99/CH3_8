// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaHUDWidget.h"

#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void USpartaHUDWidget::SetScore(int32 InScore)
{
	if (ScoreText != nullptr)
	{
		ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score : %03d"), InScore)));
	}
}
void USpartaHUDWidget::SetTime(int32 InTime)
{
	if (TimeText != nullptr)
	{
		TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time : %03d"), InTime)));
	}
}

void USpartaHUDWidget::SetHP(float InCurrentHP, float InMaxHP)
{
	if (HPBar != nullptr && InMaxHP > 0.f)
	{
		HPBar->SetPercent(InCurrentHP / InMaxHP);
	}
}