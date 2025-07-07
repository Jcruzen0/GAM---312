// Fill out your copyright notice in the Description page of Project Settings.


#include "SG_Player.h"



// Sets default values
ASG_Player::ASG_Player()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Camera Component on Player instance
	PlayerCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	PlayerCamComp->SetupAttachment(GetMesh(), "head");
	PlayerCamComp->bUsePawnControlRotation = true;
}

// Called when the game starts or when spaw
// ned
void ASG_Player::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASG_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASG_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Configure input callbacks
	PlayerInputComponent->BindAxis("MoveForward", this, &ASG_Player::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASG_Player::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASG_Player::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ASG_Player::AddControllerYawInput);
}


void ASG_Player::MoveForward(float Value)
{
	// Get forward vector
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

	// move along the forward direction depending on the value passed
	AddMovementInput(Direction, Value);
}

void ASG_Player::MoveRight(float Value)
{
	// Get right vector
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

	// move along the right vector depending on the value passed
	AddMovementInput(Direction, Value);
}
