// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"
#include "Components/SphereComponent.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);
	
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));//블루프린트에서도 디테일창에서 프리셋을 선택할 수 있으나 디폴트로 설정해둠

	Collision->SetupAttachment(Scene);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Collision);

	//이벤트 바인딩
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnItemOverlap);//충돌이 시작될때 OnItemOverlap 함수랑 이어주려면 매개변수가 같아야한다. 그러나 여기에 들어가는 매개변수 개길다.
	Collision->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnItemEndOverlap);//충돌 끝날때
}


void ABaseItem::OnItemOverlap(
	UPrimitiveComponent* OverlapComp, //충돌체 본인(콜리전 컴포넌트)
	AActor* OtherActor,//부딫힌 객체(플레이어)
	UPrimitiveComponent* OtherComp,//객체의 컴포넌트(플레이어의 캡슐컴포넌트)
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		
		ActivateItem(OtherActor);
	}
}
void ABaseItem::OnItemEndOverlap(
	UPrimitiveComponent* OverlapComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{

}
void ABaseItem::ActivateItem(AActor* Activator)
{
	
}
FName ABaseItem::GetItemType() const
{
	return ItemType;
}
void ABaseItem::DestroyItem()
{
	Destroy();
}