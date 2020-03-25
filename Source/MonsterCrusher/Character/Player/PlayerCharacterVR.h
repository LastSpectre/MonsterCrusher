// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacterVR.generated.h"

class UCameraComponent;
class UCapsuleComponent;
class UMotionControllerComponent;
class ATeleportPoint;
class AVRBowComponent;
class AWeapon;
class UChildActorComponent;
class ABullet;
class AGrenade;

UCLASS()
class MONSTERCRUSHER_API APlayerCharacterVR : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCharacterVR();

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

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Player")
	TArray<FVector> LeftHandLocations;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		USkeletalMeshComponent* RightHand = nullptr;
	
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Player")
	TArray<FVector> RightHandLocations;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		USceneComponent* TeleportShotPointRight = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		USceneComponent* TeleportShotPointLeft = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Required")
		TSubclassOf<ATeleportPoint> TeleportClass;

	// Weapon variables

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
	float ShotgunSpread = 0.0f;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player")
		TSubclassOf<ABullet> ShotgunBulletType;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		USceneComponent* LeftHandWeaponPoint = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		USceneComponent* RightHandWeaponPoint = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Player")
		void ShootShotgun(AActor* weapon);

	UFUNCTION(BlueprintCallable, Category = "Player")
		int ThrowGrenade(AActor* weapon, TArray<FVector> handPos, float Force, int grenadeCharges);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player")
		TSubclassOf<AGrenade> GrenadeType;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		TArray<FVector> GrenadePath;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Grenade")
		int GrenadeChargesLeft;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Grenade")
		int GrenadeChargesRight;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player")
		TSubclassOf<AWeapon> LeftHandWeaponType;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player")
		TSubclassOf<AWeapon> RightHandWeaponType;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		UChildActorComponent* LeftHandWeapon = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		UChildActorComponent* RightHandWeapon = nullptr;

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

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Player")
		float GrenadeCooldownLeft;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Player")
		float GrenadeCooldownRight;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player")
		float GrenadeCooldownMax;

	UFUNCTION(BlueprintImplementableEvent, Category = "Player")
		void ChangeGrenadeText();

	UFUNCTION(BlueprintCallable, Category = "Player")
		void ChangeGrenadeTextBP();

private:
	UMotionControllerComponent* m_pLeftController = nullptr;

	UMotionControllerComponent* m_pRightController = nullptr;

	ATeleportPoint* m_lastTeleportPoint = nullptr;
};
