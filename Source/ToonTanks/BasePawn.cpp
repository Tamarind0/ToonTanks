// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//creating a capsule component
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh")); //creating static mesh component
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh")); //creating static mesh component
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void ABasePawn::RotateTurret(FVector LookAtTurret)
{
	// getting the vector we want to look at by subtracting the end point - starting point
	FVector ToTargert = LookAtTurret - TurretMesh->GetComponentLocation(); // world rotation not an offset
	FRotator LookAtRotation = ToTargert.Rotation();
	LookAtRotation.Pitch = 0.f;
	LookAtRotation.Roll = 0.f;
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), 
									LookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this),
									25.f));
}

void ABasePawn::Fire()
{
	FVector projectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator projectileSpawnPointRotation = ProjectileSpawnPoint->GetComponentRotation();
	DrawDebugSphere(
		GetWorld(),
		projectileSpawnPointLocation,
		25.f,
		12,
		FColor::Red,
		false,
		3.f);
	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, projectileSpawnPointLocation, projectileSpawnPointRotation);
}
