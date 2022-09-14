// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"


//class USoundBase
UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();


private:
	class ATank* Tank;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Componets", meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
		class UProjectileMovementComponent* movementComponent;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = "Combat")
		float Damage = 100.f;
	//particles system and component
	UPROPERTY(EditAnywhere, Category = "Combat")
		class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
		class UParticleSystemComponent* TrailParticles;

	//audio
	UPROPERTY(EditAnywhere, Category = "Sound")
		class USoundBase* LaunchSound;
	UPROPERTY(EditAnywhere, Category = "Sound")
		class USoundBase* ActorHitSound;
	UPROPERTY(EditAnywhere, Category = "Sound")
		class USoundBase* SurroundingHitSound;

	//camera shake
	UPROPERTY(EditAnywhere, Category = "Camera")
		TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
