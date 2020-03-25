// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("Bullet");
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_timeAlive += DeltaTime;

	if (m_timeAlive > LifeTime)
		Destroy();

	AddActorWorldOffset(GetActorForwardVector() * Movespeed * DeltaTime);
}