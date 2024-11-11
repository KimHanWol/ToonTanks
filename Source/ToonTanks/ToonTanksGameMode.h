// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void BPStartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void BPGameOver(bool bWonGame);

public:
	
	void ActorDied(AActor* DeadActor);
	int32 GetTargetTowerCount();

private:

	void HandleGameStart();

private:

	//Data
	UPROPERTY(EditDefaultsOnly)
	float StartDelay = 3.f;

	UPROPERTY(Transient)
	int32 TargetTowerCount = 0;

	UPROPERTY(Transient)
	class ATank* Tank;

	UPROPERTY(Transient)
	class AToonTanksPlayerController* ToonTanksPlayerController;
};
