// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"
#include "Tank.h"
#include "Turret.h"
// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh")); //creating static mesh component
	ProjectileMesh->SetupAttachment(RootComponent);

	movementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	movementComponent->InitialSpeed = 1500.f;
	movementComponent->MaxSpeed = 1500.f;

	//smoke
	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticles->SetupAttachment(ProjectileMesh);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	// setting up delegate for hit event
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}
	//needed to ApplyDamage in the HealthComponent class
	AController* MyInstigator = MyOwner->GetInstigatorController();
	//needed parameter
	UClass* DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor != nullptr && OtherActor != this && OtherActor != MyOwner)
	{
		Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); // getting tank reference
		
		// Generates the damage event which will call the OnTakeDamage delegate that is in HealthComponent and will broadcast to its subscribers
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyInstigator, this, DamageTypeClass); 
		if (HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
			
		}
		// Specific audio when player or turret land a shot on each other 
		if (OtherActor == Tank)
		{
			if (ActorHitSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, ActorHitSound, GetActorLocation());
			}
		}
		else if (ATurret* Turret = Cast<ATurret>(OtherActor))
		{
			UGameplayStatics::PlaySoundAtLocation(this, ActorHitSound, GetActorLocation());
		}
		else
		{
			// sound played when the projectile hits something else but the player
			if (SurroundingHitSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SurroundingHitSound, GetActorLocation());
			}
		}

		

		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
		
	}

	Destroy();
}

