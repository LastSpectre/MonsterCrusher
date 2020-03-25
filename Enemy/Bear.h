// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Enemy/Enemy.h"
#include "Bear.generated.h"

UCLASS()
class MONSTERCRUSHER_API ABear : public AEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABear();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
