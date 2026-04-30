// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaGameMode.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"
#include "SpartaGameState.h"
#include "SpartaHUD.h"
#include "SpawnVolume.h"
#include "Kismet/GameplayStatics.h"

ASpartaGameMode::ASpartaGameMode()
{
	DefaultPawnClass = ASpartaCharacter::StaticClass();//클래스 이름을 통해 호출함 뭔소리여 어쨌튼 객체를 생성하지 않음
	//게임 모드에서 디폴트 폰 클래스를 우리가 만든 SpartaCharacter로 지정해줌
	PlayerControllerClass = ASpartaPlayerController::StaticClass();

	GameStateClass = ASpartaGameState::StaticClass();

	AccumulatedSeconds=0;
	
	MaxPlayTime=10;

	CurrentStage=1;

	HUDClass = ASpartaHUD::StaticClass();

}
void ASpartaGameMode::BeginPlay()
{
	Super::BeginPlay();
	FString CurrentLevelName = GetWorld()->GetMapName();
	CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	UE_LOG(LogTemp, Warning, TEXT("Current Level: %s"), *CurrentLevelName);

	if (CurrentLevelName == TEXT("MainMenuLevel"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Main Menu Level"));
		return;
	}
	SpawnItemsForCurrentStage();

	GetWorld()->GetTimerManager().SetTimer(
		MainTimerHandle,
		this,
		&ASpartaGameMode::HandleMainTimerElapsed,
		1.f,
		true
	);

	UE_LOG(LogTemp, Error, TEXT("Stage-%02d Started!"), CurrentStage);
}

void ASpartaGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(MainTimerHandle);
	Super::EndPlay(EndPlayReason);
}


void ASpartaGameMode::HandleMainTimerElapsed()
{
	AccumulatedSeconds += 1;

	//UE_LOG(LogTemp, Warning, TEXT("Main Timer elapsed..[%03ds]"), AccumulatedSeconds);

	UE_LOG(LogTemp, Warning, TEXT("Main timer elapsed.. [Stage-%02d][%03ds]"), CurrentStage, AccumulatedSeconds);
	
	APlayerController* PC = GetWorld()->GetFirstPlayerController();//HUD에 연결하기 위해 컨트롤러를 불러옴
		if (PC != nullptr)
		{
			ASpartaHUD* SpartaHUD = Cast<ASpartaHUD>(PC->GetHUD());
			if (SpartaHUD != nullptr)
			{
				SpartaHUD->UpdateTime(AccumulatedSeconds);
			}
		}
		
	
		if (AccumulatedSeconds % MaxPlayTime == 0)
		{
			CurrentStage += 1;
			AccumulatedSeconds = 0;

			if (CurrentStage != 4)
			{
				UE_LOG(LogTemp, Warning, TEXT("Stage-%02d Started!"), CurrentStage);

				SpawnItemsForCurrentStage();
			}
			else
			{
				if (PC != nullptr)
				{
					ASpartaHUD* SpartaHUD = Cast<ASpartaHUD>(PC->GetHUD());
					if (SpartaHUD != nullptr)
					{
						SpartaHUD->ShowGameOverMenu();
					}
				}
			}
		}

	

}



void ASpartaGameMode::SpawnItemsForCurrentStage()
{
	int32 SpawnCount = 0;

	if (CurrentStage == 1)
	{
		SpawnCount = 5;
	}

	else if (CurrentStage == 2)
	{
		SpawnCount = 10;
	}

	else if (CurrentStage == 3)
	{
		SpawnCount = 20;
	}
	TArray<AActor*> FoundSpawnVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundSpawnVolumes);

	for (AActor* Actor : FoundSpawnVolumes)
	{
		ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(Actor);
		if (SpawnVolume != nullptr)
		{
			for (int32 i = 0; i < SpawnCount; i++)
			{
				SpawnVolume->SpawnRandomItem();
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Stage %d Item Spawn Count: %d"), CurrentStage, SpawnCount);
	}
}