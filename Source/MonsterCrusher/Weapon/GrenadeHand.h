// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "GrenadeHand.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERCRUSHER_API AGrenadeHand : public AWeapon
{
	GENERATED_BODY()

public:
	AGrenadeHand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
