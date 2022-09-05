// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEnd.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"
#include "ToonTanksGameModeBase.h"
// Sets default values
AGameEnd::AGameEnd()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	BoxComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGameEnd::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Beginplay"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AGameEnd::OnOverlapBegin);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &AGameEnd::OnOverlapEnd);
	GameMode = Cast<AToonTanksGameModeBase>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void AGameEnd::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameEnd::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OVERLAPPING"));
	GameMode->FinishedLevel(OtherActor);
}

void AGameEnd::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("PAIN"));
}

