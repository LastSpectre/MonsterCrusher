// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuPlayerVR.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AMenuPlayerVR::AMenuPlayerVR()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// root component
	USceneComponent* pRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = pRoot;

	// create default camera component and attach to root
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(pRoot);

	// create default capsule component and attach to camera
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(Camera);

	// left motion controller
	m_pLeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
	m_pLeftController->SetupAttachment(pRoot);

	// set up left hand | visbile for player
	LeftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHand"));
	LeftHand->SetupAttachment(m_pLeftController);

	// right motion controller
	m_pRightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	m_pRightController->SetupAttachment(pRoot);
	m_pRightController->SetTrackingSource(EControllerHand::Right);

	// set up right hand
	RightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(m_pRightController);

	// raycast params
	// m_objectParams.Add

	Tags.Add("Player");

}

// Called when the game starts or when spawned
void AMenuPlayerVR::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMenuPlayerVR::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}