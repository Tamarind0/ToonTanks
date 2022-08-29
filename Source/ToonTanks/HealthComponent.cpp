// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameModeBase.h"
// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	//binding the event OnTakeAnyDamage to our DamageTaken func

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	
	//getting a reference to the gamemode so we can end the game when the player dies
	// casting bc UGameplayStatics::GetGameMode(this) return a GameModeBase not a AToonTankGameModeBase
	GameMode = Cast<AToonTanksGameModeBase>(UGameplayStatics::GetGameMode(this));
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//called when OnTakeAnyDamage is triggered which is triggered by the Projectile class in the Fire function when OnHit is called
void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;
	Health -= Damage;
	if (Health <= 0.f && GameMode)
	{
		GameMode->ActorDied(DamagedActor);
	}
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
}

