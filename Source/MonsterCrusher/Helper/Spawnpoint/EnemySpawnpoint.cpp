// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawnpoint.h"

#include "Components/SplineComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemySpawnpoint::AEnemySpawnpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// sphere as root component
	USphereComponent* pSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = pSphere;

	// disable collision of root
	pSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// spline component for ai follow
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(pSphere);
}