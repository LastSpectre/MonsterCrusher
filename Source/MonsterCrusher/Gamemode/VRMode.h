// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VRMode.generated.h"

class ASpawnPortals;

UCLASS()
class MONSTERCRUSHER_API AVRMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:

	AVRMode();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GameMode")
		TArray<ASpawnPortals*> SpawnPortals;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GameMode")
		APawn* PlayerPawn;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GameMode")
		bool OnePortalDestroyable;

private:
	void MakePortalDestroyable();
};
