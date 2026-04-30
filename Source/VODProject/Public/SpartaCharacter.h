// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpartaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;//입력값을 받아 움직이려면 전방선언 필요함

UCLASS()
class VODPROJECT_API ASpartaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASpartaCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth()const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float Amount);

protected:
	// Called when the game starts or when spawned
	
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;

protected:
	
	UFUNCTION()
	void Move(const FInputActionValue& value); //참조로 가져오는 이유는 복사 비용이 크기때문에 const로 값을 보호한다.
	UFUNCTION()
	void StartJump(const FInputActionValue& value);
	UFUNCTION()
	void StopJump(const FInputActionValue& value);//bool값으로 입력을 받는 함수는 나눠주는게 좋다고한다.
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);

	//스탯

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;
	void OnDeath();

private: 
	float NormalSpeed;//sprint를 위한 변수
	float SprintSpeedMultiplier;//sprint 속도에 얼마를 곱할지
	float SprintSpeed; //결국 얼마나 빨라졌는지, 앞의 두 변수를 곱한 값
	//굳이 블루프린트 외부로 노출 시킬 이유는 딱히 없어서 리플렉션 안함

};
