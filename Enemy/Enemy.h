// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class USplineComponent;
class UCapsuleComponent;
class USkeletalMeshComponent;
class APatrolPath;

UCLASS()
class MONSTERCRUSHER_API AEnemy : public ACharacter
{
	GENERATED_BODY()
	
public:
	AEnemy();

	virtual void Tick(float deltatime) override;

#pragma region move components

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	virtual void MoveEnemyActor();

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	virtual FVector CalcNextMove();

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	FVector NextSplinePointMove();
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Enemy")		
	USplineComponent* Spline = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Enemy")
	float LastPositionOnSpline = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Enemy")
	float PositionOnSpline = 0.0f;

	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
		void TakeHitDamage();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Enemy")
		int HealthPoints = 0;

	FVector m_NextPosition;

	int32 m_WayPoints;

	int32 m_CurrentWayPoint = -1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
		APatrolPath* PatrolPath;

#pragma endregion

#pragma region character components

	// UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Enemy")
	// 	UCapsuleComponent* Capsule = nullptr;

	// UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Enemy")
	// 	USkeletalMeshComponent* Mesh = nullptr;

#pragma endregion


protected:
	virtual void BeginPlay() override;
};