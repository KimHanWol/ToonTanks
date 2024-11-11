// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float Damage = 50.f;

	//Mesh
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class UStaticMeshComponent* ProjectileMesh;

	//Effect
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticles;

	//Sound
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* HitSound;

	//CameraShake
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
	
	//Component
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;
};
