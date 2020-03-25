// Fill out your copyright notice in the Description page of Project Settings.


#include "Shotgun.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/Engine.h"

// Sets default values
AShotgun::AShotgun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShotSpawnpoint = CreateDefaultSubobject<USceneComponent>(TEXT("ShotSpawnpoint"));
	ShotSpawnpoint->SetupAttachment(Weapon);
}

void AShotgun::BeginPlay()
{
	Super::BeginPlay();
	
	ShotgunCurrentShots = ShotgunMaximumShots;
}

void AShotgun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShotgun::UpdateAmmoText()
{
	UpdateAmmoTextBP();
}
