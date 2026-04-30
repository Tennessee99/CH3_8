// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "CoinItem.h"
#include "SpartaGameInstance.h"
#include "SpartaHUD.h"
#include "GameFramework/PlayerController.h"


ASpartaGameState::ASpartaGameState()
{
	Score = 0;
	SpawnedCoinCount = 0;//전체 초기화
	CollectedCoinCount = 0;
	LevelDuration = 30.0f;
	CurrentLevelIndex = 0;
	MaxLevels = 3;
}

void ASpartaGameState::BeginPlay()
{
	Super::BeginPlay();

	StartLevel();
}
int32 ASpartaGameState::GetScore() const
{
	return Score;
}

void ASpartaGameState::AddScore(int32 Amount)
{
	Score += Amount;

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if (SpartaGameInstance)
		{
			SpartaGameInstance->AddToScore(Amount);

			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			if (PC != nullptr)
			{
				ASpartaHUD* SpartaHUD = Cast<ASpartaHUD>(PC->GetHUD());
				if (SpartaHUD != nullptr)
				{
					SpartaHUD->UpdateScore(SpartaGameInstance->TotalScore);
				}
			}
		}
	}


}

void ASpartaGameState::StartLevel()
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if (SpartaGameInstance)
		{
			CurrentLevelIndex = SpartaGameInstance->CurrentLevelIndex;
		}
	}



	SpawnedCoinCount = 0;//해당레벨 초기화
	CollectedCoinCount = 0;

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	const int32 ItemToSpawn = 40;

	for (int32 i = 0; i < ItemToSpawn; ++i)
	{
		if (FoundVolumes.Num() > 0)
		{
			ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);

			if (SpawnVolume)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
				if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;//코인 개수 세기
				}
			}
		}
	}

	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&ASpartaGameState::OnLevelTimeUp,
		LevelDuration,
		false
	);

	UE_LOG(LogTemp, Warning, TEXT("Level %d Start!, Spawned %d coin"),
		CurrentLevelIndex + 1,
		SpawnedCoinCount);
}

void ASpartaGameState::OnLevelTimeUp()
{
	EndLevel();
}

void ASpartaGameState::OnCoinCollected()
{
	CollectedCoinCount++;

	UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"),
		CollectedCoinCount,
		SpawnedCoinCount);

		if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
		{
			EndLevel();
		}
}


void ASpartaGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if (SpartaGameInstance)
		{	
			
			CurrentLevelIndex++;
			SpartaGameInstance->CurrentLevelIndex = CurrentLevelIndex;
		}
	}

	if (CurrentLevelIndex >= MaxLevels)
	{
		OnGameOver();
		return;
	}
	if(LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else
	{
		OnGameOver();
	}

}
void ASpartaGameState::OnGameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over!"));
}