// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(Tank) == false)
	{
		ensure(false);
		return;
	}

	float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

	if (FireRange >= Distance)
	{
		RotateTurret(Tank->GetActorLocation());
	}
}
