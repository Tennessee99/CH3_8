// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"
#include "BaseItem.generated.h"

class USphereComponent;
UCLASS()
class VODPROJECT_API ABaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	

	ABaseItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USphereComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	UStaticMeshComponent* StaticMesh;
	
	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlapComp, //충돌체 본인(콜리전 컴포넌트)
		AActor* OtherActor,//부딫힌 객체(플레이어)
		UPrimitiveComponent* OtherComp,//객체의 컴포넌트(플레이어의 캡슐컴포넌트)
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlapComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;
	virtual void ActivateItem(AActor* Activator) override;
	virtual FName GetItemType() const override;//Fstring보다 FName이 더 가벼움
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemType;

	virtual void DestroyItem();

public:	
	

};
