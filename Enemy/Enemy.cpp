// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Own

#include "Enemy.h"
#include "Helper/Spawnpoint/EnemySpawnpoint.h"
// #include "AIController.h"
#include "Helper/Patrol/PatrolPath.h"

#pragma endregion

#pragma region Engine

// #include "Perception/PawnSensingComponent.h"
#include "Engine/World.h"
#include "Components/SplineComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

#pragma endregion

AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("Enemy");
}

// start
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	// // array for spline components
	// TArray<AActor*> FoundActors;
	// 
	// // find all spline components
	// UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawnpoint::StaticClass(), FoundActors);
	// 
	// // take first spline component, and make it path for enemy
	// Spline = ((AEnemySpawnpoint*)(FoundActors[0]))->Spline;
	// 
	// // m_WayPoints = Spline->GetNumberOfSplinePoints();
	// 
	// // m_NextPosition = CalcNextMove();
}

// update
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::MoveEnemyActor()
{	
	// // hit result for spline movement
	// FHitResult hit;
	// 
	// SetActorLocation(m_NextPosition, true, &hit);
	// 
	// // if no blocking hit
	// if (!hit.bBlockingHit)
	// 	m_NextPosition = CalcNextMove();

	// get temp position on spline from current position on spline
	// float tempPositionOnSpline = PositionOnSpline;
	// 
	// // increase temp position by movement speed
	// tempPositionOnSpline += GetWorld()->GetDeltaSeconds() * GetCharacterMovement()->MaxCustomMovementSpeed;
	// 
	// // calculate angle to target
	// FRotator rotation = Spline->GetRotationAtDistanceAlongSpline(tempPositionOnSpline, ESplineCoordinateSpace::World);
	// 
	// // rotate capsule
	// SetActorRotation(FRotator(0.0f, rotation.Yaw, 0.0f));
	// 
	// // hit result from movement
	// FHitResult hit;
	// 
	// // get location at distance of spline
	// FVector location = Spline->GetLocationAtDistanceAlongSpline(tempPositionOnSpline, ESplineCoordinateSpace::World)
	// 	/*+ FVector(0.0f, 0.0f, CapsuleComp->GetUnscaledCapsuleHalfHeight())*/;
	// 
	// // try to move capsule to next location on spline and save hit result
	// SetActorLocation(location, true, &hit);
	// 
	// // GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("REACHED"));
	// 
	// // if no blocking hit
	// if (!hit.bBlockingHit)
	// {
	// 	// set current position on spline to temp position
	// 	PositionOnSpline = tempPositionOnSpline;
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("REACHED 2"));
	// }
}	 

FVector AEnemy::CalcNextMove()
{
	// // get temp position on spline
	// LastPositionOnSpline = PositionOnSpline;
	// 
	// // increase temp position on spline
	// LastPositionOnSpline += GetWorld()->GetDeltaSeconds() * GetCharacterMovement()->MaxCustomMovementSpeed;
	// 
	// // angle to next target
	// FRotator rotation = Spline->GetRotationAtDistanceAlongSpline(LastPositionOnSpline, ESplineCoordinateSpace::World);
	// 
	// // rotate actor
	// SetActorRotation(FRotator(FRotator(0.0f, rotation.Yaw, 0.0f)));
	// 
	// FVector nextSplinePos = FVector(Spline->GetLocationAtDistanceAlongSpline(LastPositionOnSpline, ESplineCoordinateSpace::World));
	//    
	// return nextSplinePos;
	return FVector::ZeroVector;

}

FVector AEnemy::NextSplinePointMove()
{
	// if (m_CurrentWayPoint < m_WayPoints)
	// 	++m_CurrentWayPoint;
	// 
	// else
	// 	m_CurrentWayPoint = 0;
	// 
	// return Spline->GetWorldLocationAtSplinePoint(m_CurrentWayPoint);

	return FVector::ZeroVector;
}