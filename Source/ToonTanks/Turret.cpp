// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATurret::BeginPlay()
{
	Super::BeginPlay();	
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); // getting access to the tank class

}

void ATurret::Tick(float DealtaTime)
{
    Super::Tick(DealtaTime);
    if(Tank)
    {
        // find the distance to the tank
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

        // check to see if the Tank is in range
        if(Distance <= FireRange)
        {
        // if in range, rotate turret towad tank
            RotateTurret(Tank->GetActorLocation());
        }

    }
}