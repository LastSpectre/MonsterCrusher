// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

// forward declarations
class UCapsuleComponent;
class UCameraComponent;
class ATeleportPoint;
class AWeapon;
class AVRBowComponent;
class USkeletalMeshComponent;
class ABullet;
class AGrenade;

UCLASS()
class MONSTERCRUSHER_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// constructor
	APlayerPawn();

protected:
	// start
	virtual void BeginPlay() override;

public:	
	// update
	virtual void Tick(float DeltaTime) override;

	// character components
	
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
	UCapsuleComponent* Capsule = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
	UCameraComponent* Camera = nullptr;
	
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
	USceneComponent*  CameraRoot = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
	USkeletalMeshComponent* Mesh = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		USkeletalMeshComponent* LeftHand = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		USkeletalMeshComponent* RightHand = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		USceneComponent* TeleportShotPointRight = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		USceneComponent* TeleportShotPointLeft = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Required")
		TSubclassOf<ATeleportPoint> TeleportClass;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		USceneComponent* LeftHandWeaponPoint = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		USceneComponent* RightHandWeaponPoint = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Player")
		void ShootShotgun(AActor* weapon);

	UFUNCTION(BlueprintCallable, Category = "Player")
		void ThrowGrenade();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player")
		TSubclassOf<AGrenade> GrenadeType;

	float ShotgunSpread = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player")
		TSubclassOf<ABullet> ShotgunBulletType;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player")
		TSubclassOf<AWeapon> LeftHandWeaponType;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player")
		TSubclassOf<AWeapon> RightHandWeaponType;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		UChildActorComponent* LeftHandWeapon = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		UChildActorComponent* RightHandWeapon = nullptr;

	// movement components
	
	UFUNCTION(BlueprintCallable, Category = "Player")
	void Move(float ForwardBack, float LeftRight);

	UFUNCTION(BlueprintCallable, Category = "Player")
	void Rotate(float LeftRight, float UpDown);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement")
	float MoveSpeed = 450.0f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement")
	float RotationSpeed = 180.0f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement")
	float AngleLock = 45.0f;
	
	// Teleport variables
	
	bool m_TeleportActive = false;

	void Teleport();

	USceneComponent* m_ActiveTeleportShotPoint;

	UFUNCTION(BlueprintCallable, Category = "Player")
		void ActivateTeleport(USceneComponent* teleportShotPoint);

	UFUNCTION(BlueprintCallable, Category = "Player")
		void DeactivateTeleport();

	// VR Bow Variables
	UFUNCTION(BlueprintImplementableEvent, Category = "Player")
		void ShowTeleportBow(FVector startPos, FVector launchVelocity);

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		FHitResult TeleportBowHit;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		TArray<FVector> CylinderPositions;

	void CreateVRBow();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Required")
		TSubclassOf<AVRBowComponent> VRBowElementClass;

private:

	ATeleportPoint* m_lastTeleportPoint = nullptr;
};
