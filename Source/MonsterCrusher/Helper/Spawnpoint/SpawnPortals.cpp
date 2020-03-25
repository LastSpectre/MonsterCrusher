// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPortals.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "Character/Enemy/Enemy.h"
#include "Helper/Patrol/PatrolPath.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ASpawnPortals::ASpawnPortals()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// root component
	USceneComponent* pRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = pRoot;

	PortalBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalBody"));
	PortalBody->SetupAttachment(pRoot);

	EnemySpawnpoint = CreateDefaultSubobject<USceneComponent>(TEXT("EnemySpawnpoint"));
	EnemySpawnpoint->SetupAttachment(pRoot);

	Tags.Add("Portal");
}

// Called when the game starts or when spawned
void ASpawnPortals::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawnPortals::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnPortals::SpawnEnemies()
{
	
}