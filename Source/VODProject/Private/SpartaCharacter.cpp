// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaCharacter.h"
#include "EnhancedInputComponent.h"//추가
#include "SpartaPlayerController.h"
#include "Camera/CameraComponent.h"//앞에 전방선언한 내용을 여기서 인클루드
#include "GameFramework/SpringArmComponent.h"//얘도 마찬가지
#include "GameFramework/CharacterMovementComponent.h"
#include "SpartaHUD.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ASpartaCharacter::ASpartaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;//사용안할때는 꺼두는게 좋다

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp -> SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;//캐릭터를 움직일때 같이 회전할 수 있게 함

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);//스프링 암의 맨 끝부분
	CameraComp->bUsePawnControlRotation = false;//카메라는 회전을 끈다. 사실 정확히 어떻게 작동하는지는 켜봐야 알겠음;
	
	//헤더에 선언한 sprint변수들 초기화
	NormalSpeed = 600.0f;
	SprintSpeedMultiplier = 1.5f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier; 

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;//max어쩌구 즉시 캐릭터의 이동속도를 바꿔준다 사용하려면 characterMovementComponent인클루드 필요

	MaxHealth = 100.0f;//체력 초기화
	Health = MaxHealth;


}


// Called to bind functionality to input
void ASpartaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))//캐스팅한다, 왜?
	{
		if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::Move
				);
			}

			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::StartJump

				);

				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,//끝났음
					this,
					&ASpartaCharacter::StopJump//함수인데 괄호를 안붙여서 궁금했다. 괄호가 붙으면 즉시 실행, 괄호가 없으면 나중에 호출할 함수 자체를 전달하는 것. 
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::Look
				);
			}

			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::StartSprint
				);
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaCharacter::StopSprint
				);

			}



		}
	}
}

void ASpartaCharacter::Move(const FInputActionValue& value)
{
	if (!Controller) return;//컨트롤러 있는지 없는지 검사

	const FVector2D MoveInput = value.Get<FVector2D>();//인풋 컨텍스트에서 맵핑할때 2D로 설정했기 때문에

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);//X가 0이 아닐때 벡터에 집어넣어라
	}//앞뒤로 움직임

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);//Y가 0이 아닐때 벡터에 집어넣어라
	}//양옆으로 움직임
}
void ASpartaCharacter::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>())//점프 입력은 bool값을 가져오기로 했으므로 훨씬 간단하다
	{
		Jump();//엔진 내부적으로 구현된 함수. 안에서 알아서 controllercheck함
	}
}
void ASpartaCharacter::StopJump(const FInputActionValue& value)
{
	StopJumping();//얘도 마찬가지
}
void ASpartaCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);//입력에셋에서 반전했던거

}
void ASpartaCharacter::StartSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;//걷는 속도를 sprintSpeed와 같게.
	}
}
void ASpartaCharacter::StopSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;//원래 스피드로 돌아옴
	}
}

float ASpartaCharacter::GetHealth() const
{
	return Health;
}
 
void ASpartaCharacter::AddHealth(float Amount)
{
	Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);

	UE_LOG(LogTemp, Warning, TEXT("Health increased to: %f"), Health);

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC != nullptr)
	{
		ASpartaHUD* SpartaHUD = Cast<ASpartaHUD>(PC->GetHUD());
		if (SpartaHUD != nullptr)
		{
			SpartaHUD->UpdateHP(Health, MaxHealth);
		}
	}
}

float ASpartaCharacter::TakeDamage(
	float DamageAmount,
	struct FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser)

{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Health decreased to : %f"), Health);

	APlayerController* PC = Cast<APlayerController>(GetController());
	
	if (PC != nullptr)
	{
		ASpartaHUD* SpartaHUD = Cast<ASpartaHUD>(PC->GetHUD());
		if (SpartaHUD != nullptr)
		{
			SpartaHUD->UpdateHP(Health, MaxHealth);
		}
	}
	
	if (Health <= 0.0f)
	{
		OnDeath();
	}

	return ActualDamage;
}

void ASpartaCharacter::OnDeath()
{
	//게임 종료 로직
}