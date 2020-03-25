// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VRBowComponent.generated.h"

class USceneComponent;

UCLASS()
class MONSTERCRUSHER_API AVRBowComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVRBowComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Bow")
	USceneComponent* Root = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Bow")
	UStaticMeshComponent* Cylinder = nullptr;

	int m_FramesAlive = 0;
};
