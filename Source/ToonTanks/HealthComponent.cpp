// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/ToonTanksGameMode.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = MaxHealth;

	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f)
	{
		ensure(false);
		return;
	}

	CurrentHealth -= Damage;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);

	if (IsValid(ToonTanksGameMode) == true)
	{
		if (CurrentHealth <= 0)
		{
			ToonTanksGameMode->ActorDied(DamagedActor);
		}
	}
}
