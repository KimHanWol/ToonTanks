// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:

	void CheckFireCondition();
	bool InFireRange();

private:

	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 300.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRate = 2.f;

	UPROPERTY(Transient)
	class ATank* Tank;
};
