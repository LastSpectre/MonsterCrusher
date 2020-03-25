// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPortals.generated.h"

class UStaticMeshComponent;
class AEnemy;
class UChildActorComponent;
class APatrolPath;

UCLASS()
class MONSTERCRUSHER_API ASpawnPortals : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPortals();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Portal")
		UStaticMeshComponent* PortalBody;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Portal")
		USceneComponent* EnemySpawnpoint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Portal")
		TArray<AEnemy*> ActiveEnemies;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Required")
		TSubclassOf<AEnemy> EnemyClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Portal")
		APatrolPath* PathOne;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Portal")
		APatrolPath* PathTwo;

	UFUNCTION(BlueprintImplementableEvent, Category = "Portal")
		void GetDestroyEffect();

	void SpawnEnemies();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Portal")
		bool IsDestroyable;
};