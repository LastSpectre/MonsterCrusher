// Fill out your copyright notice in the Description page of Project Settings.


#include "Bear.h"

// Sets default values
ABear::ABear()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("Bear");
}

// Called when the game starts or when spawned
void ABear::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}