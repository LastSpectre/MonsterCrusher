// Fill out your copyright notice in the Description page of Project Settings.


#include "Troll.h"

// Sets default values
ATroll::ATroll()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("Troll");
}

// Called when the game starts or when spawned
void ATroll::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void ATroll::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATroll::MoveEnemyActor()
{

}