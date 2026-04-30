// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnRow.h"//GetRandomItem 함수를 사용하기 위해 불러옴
#include "SpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class VODPROJECT_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	

	ASpawnVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	UDataTable* ItemDataTable;//아이템 정보를 스폰해주는 클래스와 연결해줌

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	AActor* SpawnRandomItem();//진짜 랜덤 아이템 스폰하는 함수

	FItemSpawnRow* GetRandomItem() const;//반환 타입이 ItemSpawnRow이기때문에 파일을 인클루드 해줘야함
	AActor* SpawnItem(TSubclassOf<AActor> ItemClass);
	FVector GetRandomPointInVolume() const;
	
protected:


public:	


};
