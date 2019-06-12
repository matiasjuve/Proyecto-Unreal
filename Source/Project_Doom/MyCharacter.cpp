// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::EndJump);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMyCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMyCharacter::EndCrouch);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveVertical);
	PlayerInputComponent->BindAxis("MoveHorizontal", this, &AMyCharacter::MoverHorizontal);

	PlayerInputComponent->BindAxis("RotateX", this, &AMyCharacter::RotateCameraX);
	PlayerInputComponent->BindAxis("RotateY", this, &AMyCharacter::RotateCameraY);
}

void AMyCharacter::MoveVertical(float v)
{
	AddMovementInput(GetActorForwardVector(), v);
}

void AMyCharacter::MoverHorizontal(float h)
{
	AddMovementInput(GetActorRightVector(), h);
}

void AMyCharacter::StartJump()
{
	bPressedJump = true;
}

void AMyCharacter::EndJump()
{
	bPressedJump = false;
}

void AMyCharacter::RotateCameraX(float r)
{
	AddControllerYawInput(r);
}
void AMyCharacter::RotateCameraY(float r)
{
	AddControllerPitchInput(r);
}

void AMyCharacter::StartCrouch()
{
	Crouch();
}

void AMyCharacter::EndCrouch()
{
	UnCrouch();
}


