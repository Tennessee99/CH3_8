// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaHUD.h"
#include "Blueprint/UserWidget.h"
#include "SpartaHUDWidget.h"


ASpartaHUD::ASpartaHUD()
{
	ConstructorHelpers::FClassFinder<USpartaHUDWidget> FoundHUDWidgetClass(TEXT("/Game/Bluprints/WBP_SpartaHUD.WBP_SpartaHUD_C"));

		if (FoundHUDWidgetClass.Succeeded() == true)
		{
			HUDWidgetClass = FoundHUDWidgetClass.Class;
		}

	ConstructorHelpers::FClassFinder<UUserWidget> FoundMenuWidgetClass(TEXT("/Game/Bluprints/WBP_Menu.WBP_Menu_C"));

		if (FoundMenuWidgetClass.Succeeded() == true)
		{
			MenuWidgetClass = FoundMenuWidgetClass.Class;
		}
	ConstructorHelpers::FClassFinder<UUserWidget> FoundMainMenuWidgetClass(TEXT("/Game/Bluprints/WBP_MainMenu.WBP_MainMenu_C"));

		if (FoundMainMenuWidgetClass.Succeeded() == true)
		{
			MainMenuWidgetClass = FoundMainMenuWidgetClass.Class;
		}
}


void ASpartaHUD::BeginPlay()
{
	Super::BeginPlay();

	FString CurrentLevelName = GetWorld()->GetMapName();
	CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	if (CurrentLevelName == TEXT("MainMenuLevel"))
	{
		ShowMainMenu();
	}
	else
	{
		ShowGameHUD();
	}
}

void ASpartaHUD::ShowGameHUD()
{
	if (HUDWidgetClass != nullptr && HUDWidgetInstance == nullptr)
	{
		HUDWidgetInstance = CreateWidget<USpartaHUDWidget>(GetWorld(), HUDWidgetClass);
	}

	if (HUDWidgetInstance != nullptr)
	{
		HUDWidgetInstance->AddToViewport();
	}
}

void ASpartaHUD::ShowMainMenu()
{
	if (MainMenuWidgetClass != nullptr && MainMenuWidgetInstance == nullptr)
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
	}

	if (MainMenuWidgetInstance != nullptr)
	{
		MainMenuWidgetInstance->AddToViewport();
	}
}
void ASpartaHUD::ShowGameOverMenu()
{
	if (MenuWidgetClass != nullptr && MenuWidgetInstance == nullptr)
	{
		MenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
	}

	if (MenuWidgetInstance != nullptr)
	{
		MenuWidgetInstance->AddToViewport();
	}
}
void ASpartaHUD::UpdateScore(int32 InScore)
{

	UE_LOG(LogTemp, Warning, TEXT("ASpartaHUD::UpdateScore %d / Widget: %s"),
		InScore,
		*GetNameSafe(HUDWidgetInstance));

	if (HUDWidgetInstance != nullptr)
	{
		HUDWidgetInstance->SetScore(InScore);
	}
}

void ASpartaHUD::UpdateTime(int32 InTime)
{
	if (HUDWidgetInstance != nullptr)
	{
		HUDWidgetInstance->SetTime(InTime);
	}
}

void ASpartaHUD::UpdateHP(float InCurrentHP, float InMaxHP)
{
	UE_LOG(LogTemp, Warning, TEXT("ASpartaHUD::UpdateHP %.1f / %.1f / Widget: %s"),
		InCurrentHP,
		InMaxHP,
		*GetNameSafe(HUDWidgetInstance));

	if (HUDWidgetInstance != nullptr)
	{
		HUDWidgetInstance->SetHP(InCurrentHP, InMaxHP);
	}
}
