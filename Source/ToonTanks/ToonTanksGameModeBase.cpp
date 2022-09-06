// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameModeBase.h"
#include "Tank.h"
#include "Turret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"
#include "Templates/SubclassOf.h"


void AToonTanksGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}
void AToonTanksGameModeBase::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); // getting tank reference
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();
	//Created a delay before the player can start moving. 3s Count down
	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);
		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true);
		// created a timer that uses a delegate which call our PlayerController class to enable the input
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
	}

}
void AToonTanksGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false); //used in the gamemode blueprint, to display the player lost
	}
	else if (ATurret* DestroyedTurret = Cast<ATurret>(DeadActor)) // casting to see if the dead actor is a turret
	{
		DestroyedTurret->HandleDestruction();
		//not using below bc we want the player to reach the end not just kill all the turrets
		//TargetTowers--;
		//if (TargetTowers == 0)
		//{
		//	GameOver(true); //used in the gamemode blueprint, to display the player won
		//}
	}
	else
	{
		DeadActor->Destroy();
	}
}

void AToonTanksGameModeBase::FinishedLevel(AActor* player)
{
	if (player == Tank)
	{
		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		if (Tank)
		{
			Tank->bAlive = false;
		}
		LevelOver(true);
	}
}

int32 AToonTanksGameModeBase::GetTargetTowerCount()
{
	TArray<AActor*> towerArr;
	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), towerArr);
	return towerArr.Num();
}



