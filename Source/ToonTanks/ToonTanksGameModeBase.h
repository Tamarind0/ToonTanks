// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(AActor* DeadActor);
private:
	// getting a reference to our Tank, assigned in BeginPlay
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	float StartDelay = 3.0f;

	void HandleGameStart();

	int32 TargetTowers = 0;
	int32 GetTargetTowerCount();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

};
