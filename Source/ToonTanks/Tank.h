// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();

	APlayerController* GetPlayerController() const { return PlayerController; }
private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	void Move(float Value);
	void Turn(float VAlue);
	UPROPERTY(EditAnywhere, Category = "Movement")
	float speed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float turnRate = 100.f;

	APlayerController* PlayerController;

};
