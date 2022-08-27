// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATurret::BeginPlay()
{
	Super::BeginPlay();	
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); // getting access to the tank class

    //function bound to our timer
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true);
}

void ATurret::Tick(float DealtaTime)
{
    Super::Tick(DealtaTime);
    // check to see if the Tank is in range
    if(InRange())
    {
        // if in range, rotate turret towad tank
        RotateTurret(Tank->GetActorLocation());
    }

    
}

bool ATurret::InRange()
{
    if (Tank)
    {
        // find the distance to the tank
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

        // check to see if the Tank is in range
        if (Distance <= FireRange)
        {
            return true;
        }
    }
    return false;
}
void ATurret::CheckFireCondition()
{
    if (InRange())
    {
        Fire();
    }
}