// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

/**
 * 
 */
UCLASS()
class VODPROJECT_API AMineItem : public ABaseItem
{
	GENERATED_BODY()

public:
	AMineItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Component")//여기선 전방 선언 안하나?
	USphereComponent* ExplosionCollision;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Item")
	float ExplosionDelay;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Item")
	float ExplosionRadius;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Item")
	int32 ExplosionDamage;
	
	FTimerHandle ExplosionTimerHandle;

	virtual void ActivateItem(AActor* Activator) override;

	void Explode();
};
