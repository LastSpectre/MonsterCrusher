// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "Shotgun.generated.h"



UCLASS()
class MONSTERCRUSHER_API AShotgun : public AWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShotgun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Shotgun")
		USceneComponent* ShotSpawnpoint = nullptr;

	UFUNCTION(BlueprintImplementableEvent, Category = "Shotgun")
		void SpawnShotgunEffect();

	UFUNCTION(BlueprintImplementableEvent, Category = "Shotgun")
		void Reload();

	UFUNCTION(BlueprintImplementableEvent, Category = "Shotgun")
		void UpdateAmmoTextBP();

	UFUNCTION(BlueprintCallable, Category = "Shotgun")
		void UpdateAmmoText();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Shotgun")
		int ShotgunMaximumShots = 3;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Shotgun")
		int ShotgunCurrentShots;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Shotgun")
		bool IsReloading = false;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Shotgun")
		float ReloadTime = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Shotgun")
		float CurrentReloadTime = 0.0f;
};
