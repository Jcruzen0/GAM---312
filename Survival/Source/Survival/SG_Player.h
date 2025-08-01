// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Resource_M.h"
#include "SG_ObjectivesUI.h"
#include "SG_BuildingPart.h"
#include "SG_PlayerHUD.h"
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

	UFUNCTION()
	void FindObject();

	// Create a camera component
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* PlayerCamComp;


	// Player's current health value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Health = 100.0f;

	//Player's current hunger value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Hunger = 100.0f;

	// Player's current stamina value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Stamina = 100.0f;

	// Amount of wood the player currently holds
	UPROPERTY(EditAnywhere, Category = "Resources")
	int Wood;

	// Amount of stone the player currently holds
	UPROPERTY(EditAnywhere, Category = "Resources")
	int Stone;

	// Amount of berries the player currently holds
	UPROPERTY(EditAnywhere, Category = "Resources")
	int Berry;

	// Array storing resource amounts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TArray<int> ResourcesArray;

	// Array storing resource names corresponding to ResourcesArray
	UPROPERTY(EditAnywhere, Category = "Resources")
	TArray<FString> ResourcesNameArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Supplies")
	TArray<int> BuildingArray;

	UPROPERTY()
	bool bIsBuilding;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ASG_BuildingPart> BuildingPartClass;

	UPROPERTY()
	ASG_BuildingPart* BuildingPart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USG_PlayerHUD* PlayerHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USG_ObjectivesUI* ObjectiveUI;
	
	UPROPERTY()
	float BuiltObjectives;
	
	UPROPERTY()
	float MaterialsCollected;

	// Sets the player's health to a new value
	UFUNCTION(BlueprintCallable)
	void SetHealth(float Value);

	// Sets the player's hunger to a new value
	UFUNCTION(BlueprintCallable)
	void SetHunger(float Value);

	// Sets the player's stamina to a new value
	UFUNCTION(BlueprintCallable)
	void SetStamina(float Value);

	// Decreases player stats over time
	UFUNCTION()
	void DecreaseStats();

	// Adds resource value to the player's inventory based on resource type
	UFUNCTION()
	void GiveResource(float Value, FString ResourceType);

	UFUNCTION(BlueprintCallable)
	void UpdateResources(float woodAmount, float stoneAmount, FString buildingObject);

	UFUNCTION(BlueprintCallable)
	void SpawnBuilding(int buildingID, bool& isSuccess);

	UFUNCTION()
	void RotateBuilding();
};
