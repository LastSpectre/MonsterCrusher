// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MenuPlayerVR.generated.h"

class UCameraComponent;
class UCapsuleComponent;
class UMotionControllerComponent;

UCLASS()
class MONSTERCRUSHER_API AMenuPlayerVR : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMenuPlayerVR();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		UCameraComponent* Camera = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		UCapsuleComponent* Capsule = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		USkeletalMeshComponent* LeftHand = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		USkeletalMeshComponent* RightHand = nullptr;

private:
	UMotionControllerComponent* m_pLeftController = nullptr;

	UMotionControllerComponent* m_pRightController = nullptr;

};
