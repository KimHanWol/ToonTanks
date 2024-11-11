// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Projectile.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	ParticleSystemComponent->SetupAttachment(RootComponent);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (IsValid(LaunchSound) == true)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this, 
			LaunchSound, 
			GetActorLocation(), 
			GetActorRotation()
			);
	}
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* InOwner = GetOwner();
	if (IsValid(InOwner) == false)
	{
		ensure(false);
		Destroy();
		return;
	}

 	AController* OwnerController = InOwner->GetInstigatorController();
	if (IsValid(OwnerController) == false)
	{
		ensure(false);
		Destroy();
		return;
	}

	UClass* DamageTypeClass = UDamageType::StaticClass();

	if (IsValid(OtherActor) == true && OtherActor != this && OtherActor != InOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, OwnerController, InOwner, DamageTypeClass);

		if (IsValid(HitParticles) == true)
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				this, 
				HitParticles, 
				GetActorLocation(), 
				GetActorRotation()
				);
		}

		if (IsValid(HitSound) == true)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this, 
				HitSound, 
				GetActorLocation(), 
				GetActorRotation()
				);
		}

		if (IsValid(HitCameraShakeClass) == true)
		{
			if (IsValid(GetWorld()) == true && IsValid(GetWorld()->GetFirstPlayerController()) == true)
			{
				GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
			}
		}

		Destroy();
	}
}
