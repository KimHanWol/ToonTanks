// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "ToonTanks/Tank.h"
#include "ToonTanks/ToonTanksPlayerController.h"
#include "ToonTanks/Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		if (IsValid(ToonTanksPlayerController) == true)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}

		BPGameOver(false);

		Tank->HandleDestruction();
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		--TargetTowerCount;
		if (TargetTowerCount <= 0)
		{
			BPGameOver(true);
		}
	}
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> TowerActors;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), TowerActors);
	return TowerActors.Num();
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowerCount = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	BPStartGame();

	if (IsValid(ToonTanksPlayerController) == true)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true
		);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
	}
}
