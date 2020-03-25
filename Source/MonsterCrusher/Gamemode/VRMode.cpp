// Fill out your copyright notice in the Description page of Project Settings.


#include "VRMode.h"
#include "Helper/Spawnpoint/SpawnPortals.h"
#include "Engine/Engine.h"

AVRMode::AVRMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AVRMode::BeginPlay()
{
	Super::BeginPlay();
}

void AVRMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MakePortalDestroyable();
}

void AVRMode::MakePortalDestroyable()
{
	// if there are still portals in the array
	if (SpawnPortals.Num() > 0)
	{
		if (!OnePortalDestroyable)
		{
			int index = FMath::RandRange(0, SpawnPortals.Num() - 1);

			SpawnPortals[index]->IsDestroyable = true;

			SpawnPortals[index]->GetDestroyEffect();

			SpawnPortals.RemoveAt(index);

			OnePortalDestroyable = true;
		}
	}
}