// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SpartaHUD.generated.h"

class USpartaHUDWidget;
class UUserWidget;
class UMainMenuWidget;
/**
 * 
 */

UCLASS()
class VODPROJECT_API ASpartaHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ASpartaHUD();

	virtual void BeginPlay() override;

	void ShowGameHUD();

	void UpdateScore(int32 InScore);

	void UpdateTime(int32 InTime);

	void UpdateHP(float InCurrentHP, float InMaxHp);

	void ShowGameOverMenu();

	void ShowMainMenu();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USpartaHUDWidget> HUDWidgetClass;

	UPROPERTY()
	USpartaHUDWidget* HUDWidgetInstance;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> MenuWidgetClass;

	UPROPERTY()
	UUserWidget* MenuWidgetInstance;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;  

	UPROPERTY()
	UUserWidget* MainMenuWidgetInstance;

};
