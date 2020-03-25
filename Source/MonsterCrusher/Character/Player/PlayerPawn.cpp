// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Helper/Teleport/TeleportPoint.h"
#include "Weapon/Weapon.h"
#include "Weapon/Shotgun.h"
#include "Helper/Teleport/VRBowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapon/Bullet.h"
#include "Engine/Engine.h"
#include "Weapon/Grenade.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	// enable update
	PrimaryActorTick.bCanEverTick = true;

	// create scene component
	USceneComponent* pRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// set root component
	RootComponent = pRoot;

	// create capsule component and attach to root
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(pRoot);

	// mesh component
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Capsule);

	// Camera root component
	CameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	CameraRoot->SetupAttachment(Capsule);

	// camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraRoot);

	// set up left hand | visbile for player
	LeftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHand"));
	LeftHand->SetupAttachment(Capsule);

	// set left teleport point
	TeleportShotPointLeft = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportShotPointLeft"));
	TeleportShotPointLeft->SetupAttachment(LeftHand);

	// left weaponpoint | currently rotated for Shotgun
	LeftHandWeaponPoint = CreateDefaultSubobject<USceneComponent>(TEXT("LeftHandWeaponPoint"));
	LeftHandWeaponPoint->SetupAttachment(LeftHand);

	// set up right hand
	RightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(Capsule);

	// set right teleport point
	TeleportShotPointRight = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportShotPointRight"));
	TeleportShotPointRight->SetupAttachment(RightHand);

	// right weapon point | currently rotated for Shotgun
	RightHandWeaponPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RightHandWeaponPoint"));
	RightHandWeaponPoint->SetupAttachment(RightHand);

	// set up left weapon
	LeftHandWeapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("LeftHandWeapon"));
	LeftHandWeapon->SetupAttachment(LeftHandWeaponPoint);

	// set up right weapon
	RightHandWeapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("RightHandWeapon"));
	RightHandWeapon->SetupAttachment(RightHandWeaponPoint);

	// tags
	Tags.Add("Player");
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	LeftHandWeapon->SetChildActorClass(LeftHandWeaponType);
	RightHandWeapon->SetChildActorClass(RightHandWeaponType);

	// offset mit tangens von 5° | um auszurechnen wie die gegenkatethe ist | ankathete ist velocity * lifetime
	ShotgunSpread = UKismetMathLibrary::DegTan(5.0f) * (4000.0f * 0.6f);

	// GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::SanitizeFloat(ShotgunSpread));
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if player doesnt wants to tp return
	if (!m_TeleportActive)
		return;

	//Teleport();

	CreateVRBow();
}

// controls the player movement | normal
void APlayerPawn::Move(float ForwardBack, float LeftRight)
{
	FVector dir = Capsule->GetForwardVector() * ForwardBack;
	dir += Capsule->GetRightVector() * LeftRight;
	dir.Normalize();
	dir *= GetWorld()->GetDeltaSeconds() * MoveSpeed;

	Capsule->AddWorldOffset(dir, true);
}

// controls the player rotation
void APlayerPawn::Rotate(float LeftRight, float UpDown)
{
	// yaw rotation | looking left and right
	FRotator rotation = FRotator(0.0f, LeftRight * GetWorld()->GetDeltaSeconds() * RotationSpeed, 0.0f);
	Capsule->AddLocalRotation(rotation);

	// calculate pitch rotation | looking up and down
	rotation = FRotator(UpDown * GetWorld()->GetDeltaSeconds() * RotationSpeed, 0.0f, 0.0f);

	// lock up and down angles
	if (CameraRoot->RelativeRotation.Pitch + rotation.Pitch > AngleLock || CameraRoot->RelativeRotation.Pitch + rotation.Pitch < -AngleLock)
		return;

	CameraRoot->AddLocalRotation(rotation);
}

void APlayerPawn::ShootShotgun(AActor* weapon)
{
	// spawn bullet
	AShotgun* CurrentShotgun = ((AShotgun*)weapon);
	CurrentShotgun->SpawnShotgunEffect();

	FVector target = CurrentShotgun->ShotSpawnpoint->GetComponentLocation() + CurrentShotgun->ShotSpawnpoint->GetForwardVector() * 0.6f * 4000.0f;

	// Spawns 8 Bullets with random spread
	for (int i = 0; i < 8; i++)
	{
#pragma region Doesnt work correctly

		// calculate shotgun offset for random spread
		float offsetY = UKismetMathLibrary::RandomFloatInRange(-ShotgunSpread, ShotgunSpread);
		float offsetZ = UKismetMathLibrary::RandomFloatInRange(-ShotgunSpread, ShotgunSpread);

		FVector temp = FVector(target.X, target.Y + offsetY, target.Z + offsetZ);

		// Spawn a bullet at the ShotSpawnpoint pos and rotate it towards the target vector
		ABullet* bullet = GetWorld()->SpawnActor<ABullet>(ShotgunBulletType,
			CurrentShotgun->ShotSpawnpoint->GetComponentLocation(),
			UKismetMathLibrary::FindLookAtRotation(CurrentShotgun->ShotSpawnpoint->GetComponentLocation(), temp));

#pragma endregion

#pragma region another try

		// // save correct position of ShotSpawnpoint
		// FVector correctPos = (CurrentShotgun->ShotSpawnpoint->GetComponentLocation());
		// 
		// FVector offsetHorizontal = CurrentShotgun->ShotSpawnpoint->GetRightVector();
		// 
		// UKismetMathLibrary::Vector_Normalize(offsetHorizontal);
		// 
		// int sign = UKismetMathLibrary::RandomIntegerInRange(0, 1);
		// 
		// if (sign == 0)
		// {
		// 	for (int sum = 0; sum < ShotgunSpread; sum++)
		// 	{
		// 		correctPos += offsetHorizontal;
		// 	}
		// }
		// else
		// {
		// 	for (int sum = 0; sum > ShotgunSpread; sum--)
		// 	{
		// 		correctPos -= offsetHorizontal;
		// 	}
		// }
		// 
		// correctPos.Y += offsetY;
		// 
		// FVector temp = correctPos + correctPos.ForwardVector * 4000.0f;
		// 
		// // Spawn a bullet at the ShotSpawnpoint pos and rotate it towards the target vector
		// ABullet* bullet = GetWorld()->SpawnActor<ABullet>(ShotgunBulletType,
		// 	CurrentShotgun->ShotSpawnpoint->GetComponentLocation(),
		// 	UKismetMathLibrary::FindLookAtRotation(CurrentShotgun->ShotSpawnpoint->GetComponentLocation(), temp));

#pragma endregion		
	}
}

void APlayerPawn::ThrowGrenade()
{
	AGrenade* grenade = GetWorld()->SpawnActor<AGrenade>(GrenadeType,
		RightHandWeaponPoint->GetComponentLocation(),
		RightHandWeaponPoint->GetComponentRotation());

	FVector ThrowDirection = RightHandWeaponPoint->GetForwardVector() * 2000.0f;

	grenade->Weapon->AddImpulse(ThrowDirection);
}

// controls player teleportation
void APlayerPawn::Teleport()
{
	// raycast result
	FHitResult hit;

	// direction of ray
	FVector target = m_ActiveTeleportShotPoint->GetComponentLocation() + m_ActiveTeleportShotPoint->GetForwardVector() * 1000.0f;

	// shoot ray
	GetWorld()->LineTraceSingleByChannel(hit, m_ActiveTeleportShotPoint->GetComponentLocation(), target, ECollisionChannel::ECC_Camera);

	// if nothing was hit
	if (!hit.GetComponent())
	{
		return;
	}

	// if hit component is not floor return
	if (!hit.GetComponent()->ComponentHasTag("Floor"))
	{
		// destroy last tp indicator
		if (m_lastTeleportPoint != nullptr)
		{
			m_lastTeleportPoint->DestroySelf();
		}
		return;
	}

	// if hit target is floor create an indicator
	ATeleportPoint* TargetPoint = GetWorld()->SpawnActor<ATeleportPoint>(TeleportClass, hit.Location, FRotator());

	// destroy last tp indicator
	if (m_lastTeleportPoint != nullptr)
	{
		m_lastTeleportPoint->DestroySelf();
	}

	// set new indicator as last
	m_lastTeleportPoint = TargetPoint;
}

// activates tp functionality
void APlayerPawn::ActivateTeleport(USceneComponent* teleportShotPoint)
{
	m_ActiveTeleportShotPoint = teleportShotPoint;

	m_TeleportActive = true;
}

// deactivates tp functionality and destroyes last indicator
void APlayerPawn::DeactivateTeleport()
{
	m_TeleportActive = false;

	// if player had a valid tp point when released
	if (m_lastTeleportPoint != nullptr)
	{
		SetActorLocation(m_lastTeleportPoint->GetActorLocation());
		AddActorWorldOffset(FVector(0.0f, 0.0f, Capsule->GetScaledCapsuleHalfHeight() + 2));

		//Capsule->SetWorldLocation(m_lastTeleportPoint->GetActorLocation());
		//Capsule->AddWorldOffset(FVector(0.0f, 0.0f, Capsule->GetScaledCapsuleHalfHeight()));

		Capsule->SetRelativeLocation(FVector::ZeroVector);
	}

	if (m_lastTeleportPoint)
		m_lastTeleportPoint->DestroySelf();

	m_lastTeleportPoint = nullptr;
}

void APlayerPawn::CreateVRBow()
{
	ShowTeleportBow(m_ActiveTeleportShotPoint->GetComponentLocation(), m_ActiveTeleportShotPoint->GetForwardVector() * 900);

	for (int i = 0; i < CylinderPositions.Num() - 1; i++)
	{
		AVRBowComponent* BowElem = GetWorld()->SpawnActor<AVRBowComponent>(VRBowElementClass, CylinderPositions[i], FRotator());
		BowElem->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(CylinderPositions[i], CylinderPositions[i + 1]));
		BowElem->Cylinder->SetRelativeScale3D(FVector(0.1f, 0.1f, FVector::Distance(CylinderPositions[i + 1], CylinderPositions[i]) / 100.0f));
		BowElem->Cylinder->SetRelativeLocation(FVector((BowElem->Cylinder->RelativeScale3D.Z / 2) * 100.0f, BowElem->Cylinder->RelativeLocation.Y, BowElem->Cylinder->RelativeLocation.Z));
	}

	// if nothing was hit
	if (!TeleportBowHit.GetComponent())
	{
		return;
	}

	// if hit component is not floor return
	if (!TeleportBowHit.GetComponent()->ComponentHasTag("Floor"))
	{
		// destroy last tp indicator and bow
		if (m_lastTeleportPoint != nullptr)
		{
			m_lastTeleportPoint->DestroySelf();
		}
		return;
	}

	// if hit target is floor create an indicator
	ATeleportPoint* TargetPoint = GetWorld()->SpawnActor<ATeleportPoint>(TeleportClass, TeleportBowHit.Location, FRotator());

	// destroy last tp indicator
	if (m_lastTeleportPoint != nullptr)
	{
		m_lastTeleportPoint->DestroySelf();
	}

	// set new indicator as last
	m_lastTeleportPoint = TargetPoint;
}

