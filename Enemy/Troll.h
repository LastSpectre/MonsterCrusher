// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Enemy/Enemy.h"
#include "Troll.generated.h"

UCLASS()
class MONSTERCRUSHER_API ATroll : public AEnemy
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATroll();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void MoveEnemyActor() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
		TSubclassOf<AController> MyAIControllerClass;
};