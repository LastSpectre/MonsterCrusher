// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// controller isnt allowed to rotate on his own
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// turns character to direction moving
	GetCharacterMovement()->bOrientRotationToMovement = true;
		
	// sets rotation speed of yaw axis
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	// sets air control speed
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookLeftRight", this, &APawn::AddControllerYawInput /*&APlayerCharacter::RotateLeftRight*/);
	PlayerInputComponent->BindAxis("LookUpDown", this, &APawn::AddControllerPitchInput /*&APlayerCharacter::RotateUpDown*/);

	PlayerInputComponent->BindAxis("MoveForwardBack", this, &APlayerCharacter::MoveForwardBack);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &APlayerCharacter::MoveLeftRight);
}

void APlayerCharacter::MoveForwardBack(float ForwardBack)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	// gets forward direction from camera in a very complicated way
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// FVector Direction = FollowCamera->GetForwardVector();

	AddMovementInput(Direction, ForwardBack);
}

void APlayerCharacter::MoveLeftRight(float LeftRight)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	// gets left right direction from camera in a very complicated way
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// FVector Direction = FollowCamera->GetRightVector();

	AddMovementInput(Direction, LeftRight);
}

// void APlayerCharacter::RotateUpDown(float UpDown)
// {
// 	// calculate pitch rotation | looking up and down
// 	FRotator rotation = FRotator(UpDown * GetWorld()->GetDeltaSeconds() * 180.0f, 0.0f, 0.0f);
// 
// 	// lock up and down angles
// 	if (FollowCamera->RelativeRotation.Pitch + rotation.Pitch > 45.0f || FollowCamera->RelativeRotation.Pitch + rotation.Pitch < -45.0f)
// 		return;
// 
// 	FollowCamera->AddLocalRotation(rotation);
// }
// 
// void APlayerCharacter::RotateLeftRight(float LeftRight)
// {
// 	// yaw rotation | looking left and right
// 	FRotator rotation = FRotator(0.0f, LeftRight * GetWorld()->GetDeltaSeconds() * 180.0f, 0.0f);
// 	AddActorLocalRotation(rotation);
// }