// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Componets", meta = (AllowPrivateAccess = true))
	class UCapsuleComponent* CapsuleComp; //forward declaration pointer since UCapsuleComponent is not already included in actors

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Componets", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* BaseMesh;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Componets", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Componets", meta = (AllowPrivateAccess = true))
	USceneComponent* ProjectileSpawnPoint;

	// used to spawn our blueprint projectile
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	//paticle system
	UPROPERTY(EditAnywhere, Category = "Combat")
		class UParticleSystem* DeathParticles;

	//audio
		//audio
	UPROPERTY(EditAnywhere, Category = "Sound")
		class USoundBase* DeathSound;
	//camera shake
	UPROPERTY(EditAnywhere, Category = "Camera")
		TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

protected:
	void RotateTurret(FVector LookAtTurret);
	void Fire();
	void HandleDestruction();
};
