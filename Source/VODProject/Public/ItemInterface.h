// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface//리플렉션을 위한 인터페이스 수정 x
{
	GENERATED_BODY()
};

/**
 * 
 */
class VODPROJECT_API IItemInterface
{
	GENERATED_BODY()

	
public:


	UFUNCTION()
	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlapComp, //충돌체 본인(콜리전 컴포넌트)
		AActor* OtherActor,//부딫힌 객체(플레이어)
		UPrimitiveComponent* OtherComp,//객체의 컴포넌트(플레이어의 캡슐컴포넌트)
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) = 0;


	UFUNCTION()
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlapComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) = 0;//앞의 함수에서 매개변수 두개가 빠진다.
	virtual void ActivateItem(AActor* Activator) = 0;
	virtual FName GetItemType() const = 0;//Fstring보다 FName이 더 가벼움
	


	//지뢰, 힐링, 코인
	//힐링, 코인 - 즉시 발동형 - 오버랩
	//지뢰 =범위 내에 오버랩 - 발동이 5초뒤 폭발 - 오버랩 - 데미지


};
