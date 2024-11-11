// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CupsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CupsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CupsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	if (IsValid(DeathParticles) == true)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			this,
			DeathParticles,
			GetActorLocation(),
			GetActorRotation()
			);
	}

	if (IsValid(DeathSound) == true)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this, 
			DeathSound, 
			GetActorLocation(), 
			GetActorRotation()
			);
	}

	if (IsValid(DeathCameraShakeClass) == true)
	{
		if (IsValid(GetWorld()) == true && IsValid(GetWorld()->GetFirstPlayerController()) == true)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
		}
	}

	// TODO: Visual/sound effect
}

void ABasePawn::RotateTurret(const FVector& LookAtTarget)
{
	if (IsValid(TurretMesh) == false)
	{
		ensure(false);
		return;
	}

	const FVector& ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f); //터렛이 아래를 바라보지 않게 하기 위해서 Yaw 만 적용

	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this), 25.f));
}

void ABasePawn::Fire()
{
	if (IsValid(ProjectileSpawnPoint) == false)
	{
		ensure(false);
		return;
	}

	const FVector& Location = ProjectileSpawnPoint->GetComponentLocation();
	const FRotator& Rotation= ProjectileSpawnPoint->GetComponentRotation();

	AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	SpawnedProjectile->SetOwner(this);
}
