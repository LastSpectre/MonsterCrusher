// Fill out your copyright notice in the Description page of Project Settings.


#include "VRBowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AVRBowComponent::AVRBowComponent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// root component
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// cylinder component
	Cylinder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cylinder"));
	Cylinder->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AVRBowComponent::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AVRBowComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_FramesAlive > 0)
		Destroy();

	m_FramesAlive++;
}

