// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "SG_Player.generated.h"

UCLASS()
class SURVIVAL_API ASG_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASG_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Callback when forward inputs are pressed 
	UFUNCTION()
	void MoveForward(float Value);

	// Callback when right movements are pressed
	UFUNCTION()
	void MoveRight(float Value);

	// Create a camera component
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* PlayerCamComp;
	
};
