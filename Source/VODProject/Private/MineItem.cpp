// Fill out your copyright notice in the Description page of Project Settings.


#include "MineItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"//데미지 입히는 함수 호출할때 필요하다

AMineItem::AMineItem()
{
	ExplosionDelay = 5.0f;
	ExplosionRadius = 300.0f;
	ExplosionDamage = 30.0f;

	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(ExplosionRadius);
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ExplosionCollision->SetupAttachment(Scene);

	

	ItemType = "Mine";
}

void AMineItem::ActivateItem(AActor* Activator)
{
	
	//타이머 핸들러
	GetWorld()->GetTimerManager().SetTimer(
		ExplosionTimerHandle,
		this,
		&AMineItem::Explode,
		ExplosionDelay
	);
}

void AMineItem::Explode( )
{
	TArray<AActor*> OverlappingActors;
	ExplosionCollision->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			UGameplayStatics::ApplyDamage(
				Actor,
				ExplosionDamage,
				nullptr,
				this,
				UDamageType::StaticClass()
			);//언리얼에서 제공하는 데미지 시스템
		}
	}

	DestroyItem();
}