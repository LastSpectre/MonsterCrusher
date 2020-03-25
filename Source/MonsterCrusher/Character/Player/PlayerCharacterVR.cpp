// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterVR.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "MotionControllerComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Helper/Teleport/TeleportPoint.h"
// #include "NavigationSystem.h"
#include "Helper/Teleport/VRBowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Shotgun.h"
#include "Weapon/Weapon.h"
#include "Components/ChildActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Weapon/ShotgunBullet.h"
#include "CollisionQueryParams.h"
#include "Weapon/Bullet.h"
#include "Weapon/Grenade.h"


// Sets default values
APlayerCharacterVR::APlayerCharacterVR()
{
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

	// set left teleport point
	TeleportShotPointLeft = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportShotPointLeft"));
	TeleportShotPointLeft->SetupAttachment(LeftHand);

	// left weaponpoint | currently rotated for Shotgun
	LeftHandWeaponPoint = CreateDefaultSubobject<USceneComponent>(TEXT("LeftHandWeaponPoint"));
	LeftHandWeaponPoint->SetupAttachment(LeftHand);

	// right motion controller
	m_pRightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	m_pRightController->SetupAttachment(pRoot);
	m_pRightController->SetTrackingSource(EControllerHand::Right);

	// set up right hand
	RightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(m_pRightController);

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

	Tags.Add("Player");
}

// Called when the game starts or when spawned
void APlayerCharacterVR::BeginPlay()
{
	Super::BeginPlay();

	LeftHandWeapon->SetChildActorClass(LeftHandWeaponType);
	RightHandWeapon->SetChildActorClass(RightHandWeaponType);

	ShotgunSpread = UKismetMathLibrary::DegTan(5.0f) * (4000.0f * 0.6f);

	GrenadeChargesLeft = 2;
	GrenadeChargesRight = 2;

	ChangeGrenadeText();
}

// Called every frame
void APlayerCharacterVR::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// track left hand
	LeftHandLocations.Add(LeftHand->GetComponentLocation());

	if (LeftHandLocations.Num() > 10)
		LeftHandLocations.RemoveAt(0);

	// track right hand
	RightHandLocations.Add(RightHand->GetComponentLocation());

	if (RightHandLocations.Num() > 10)
		RightHandLocations.RemoveAt(0);

	// reset grenades
	GrenadeCooldownLeft += DeltaTime;

	if (GrenadeCooldownLeft >= 15.0f)
	{
		if (GrenadeChargesLeft < 2)
		{
			++GrenadeChargesLeft;
			GrenadeCooldownLeft = 0.0f;
			ChangeGrenadeText();
		}
	}

	GrenadeCooldownRight += DeltaTime;

	if (GrenadeCooldownRight >= 15.0f)
	{
		if (GrenadeChargesRight < 2)
		{
			++GrenadeChargesRight;
			GrenadeCooldownRight = 0.0f;
			ChangeGrenadeText();
		}
	}

	// if player doesnt wants to tp return
	if (!m_TeleportActive)
		return;

	CreateVRBow();
}

void APlayerCharacterVR::ShootShotgun(AActor* weapon)
{
	// spawn bullet
	AShotgun* CurrentShotgun = ((AShotgun*)weapon);

	// if shotgun is empty
	if (CurrentShotgun->ShotgunCurrentShots == 0)
	{
		// if shotgun is not reloading
		if (!(CurrentShotgun->IsReloading))
		{
			CurrentShotgun->Reload();
		}

		return;
	}

	CurrentShotgun->SpawnShotgunEffect();

	CurrentShotgun->ShotgunCurrentShots -= 1;

	CurrentShotgun->UpdateAmmoText();

	// Spawns 8 Bullets with random spread
	for (int i = 0; i < 8; i++)
	{
		FVector target = CurrentShotgun->ShotSpawnpoint->GetComponentLocation() + CurrentShotgun->ShotSpawnpoint->GetForwardVector() * 0.6f * 4000.0f;

		FVector right = CurrentShotgun->ShotSpawnpoint->GetRightVector();
		FVector up = CurrentShotgun->ShotSpawnpoint->GetUpVector();

		// calculate shotgun offset for random spread
		float offsetY = UKismetMathLibrary::RandomFloatInRange(-ShotgunSpread, ShotgunSpread);
		float offsetZ = UKismetMathLibrary::RandomFloatInRange(-ShotgunSpread, ShotgunSpread);

		right = right * offsetY;
		up = up * offsetZ;

		FVector temp = target + right + up;

		// Spawn a bullet at the ShotSpawnpoint pos and rotate it towards the target vector
		ABullet* bullet = GetWorld()->SpawnActor<ABullet>(ShotgunBulletType,
			CurrentShotgun->ShotSpawnpoint->GetComponentLocation(),
			UKismetMathLibrary::FindLookAtRotation(CurrentShotgun->ShotSpawnpoint->GetComponentLocation(), temp));
	}
}

int APlayerCharacterVR::ThrowGrenade(AActor * weapon, TArray<FVector> handPos, float Force, int grenadeCharges)
{
	if (grenadeCharges == 0)
		return 0;

	AGrenade* grenade = GetWorld()->SpawnActor<AGrenade>(GrenadeType,
		weapon->GetActorLocation(),
		weapon->GetActorRotation());

	FVector forceDirection;

	for (FVector pos : handPos)
	{
		forceDirection += pos;
	}

	forceDirection /= handPos.Num();

	forceDirection -= weapon->GetActorLocation();
	forceDirection *= -1;

	grenade->Weapon->AddImpulse(forceDirection * Force);

	grenadeCharges--;

	return grenadeCharges;
}

void APlayerCharacterVR::Teleport()
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

void APlayerCharacterVR::ActivateTeleport(USceneComponent* teleportShotPoint)
{
	m_ActiveTeleportShotPoint = teleportShotPoint;

	m_TeleportActive = true;
}

void APlayerCharacterVR::DeactivateTeleport()
{
	m_TeleportActive = false;

	// if player had a valid tp point when released
	if (m_lastTeleportPoint != nullptr)
	{
		SetActorLocation(m_lastTeleportPoint->GetActorLocation());
		AddActorWorldOffset(FVector(0.0f, 0.0f, Capsule->GetScaledCapsuleHalfHeight() + 2));

		Capsule->SetRelativeLocation(FVector::ZeroVector);
	}

	if (m_lastTeleportPoint)
	{
		m_lastTeleportPoint->DestroySelf();
	}

	m_lastTeleportPoint = nullptr;
}

void APlayerCharacterVR::CreateVRBow()
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

void APlayerCharacterVR::ChangeGrenadeTextBP()
{
	ChangeGrenadeText();
}
