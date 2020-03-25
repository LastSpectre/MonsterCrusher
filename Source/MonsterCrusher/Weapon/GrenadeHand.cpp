// Fill out your copyright notice in the Description page of Project Settings.


#include "GrenadeHand.h"

AGrenadeHand::AGrenadeHand()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("Grenade");
}

void AGrenadeHand::BeginPlay()
{
	Super::BeginPlay();
}

void AGrenadeHand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
