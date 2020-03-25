// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class MONSTERCRUSHER_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Bullet")
		float BulletDamage = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Bullet")
		float Movespeed = 4000.0f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Bullet")
		float LifeTime = 0.6f;

private:
	float m_timeAlive = 0.0f;
};
