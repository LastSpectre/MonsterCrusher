// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnpoint.generated.h"

class USplineComponent;

UCLASS()
class MONSTERCRUSHER_API AEnemySpawnpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawnpoint();

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Enemy")
	USplineComponent* Spline = nullptr;

};
