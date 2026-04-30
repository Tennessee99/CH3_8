// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaPlayerController.h"
#include "EnhancedInputSubsystems.h"

ASpartaPlayerController::ASpartaPlayerController()
	: InputMappingContext(nullptr)
	, MoveAction(nullptr)
	, JumpAction(nullptr)
	, LookAction(nullptr)
	, SprintAction(nullptr)
{

}

void ASpartaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())//화면 관리
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())//입력 시스템을 관리하는 코드

		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);//0은 우선순위. 0순위라는 뜻
			}
		}
	}
}