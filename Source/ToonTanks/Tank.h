// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:

	ATank();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const struct FInputActionValue& Value);
	void Turn(const struct FInputActionValue& Value);


private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputMappingContext* DefaultContext;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* TurnAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 45.f;

	UPROPERTY(Transient)
	APlayerController* PlayerController;
};
