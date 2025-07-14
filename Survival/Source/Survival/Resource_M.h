// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Resource_M.generated.h"

UCLASS()
class SURVIVAL_API AResource_M : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AResource_M();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Name of the resource
	UPROPERTY(EditAnywhere)
	FString ResourceName = "Wood";

	// Amount of resource given to the player per interaction
	UPROPERTY(EditAnywhere)
	int ResourceAmount = 5;

	// Total amount of this resource available
	UPROPERTY(EditAnywhere)
	int TotalResource = 100;

	// Text render component to display the resource name above the object
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* ResourceNameTxt;

	// Mesh component representing the resource in the world
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	// The static mesh asset used for this resource
	UPROPERTY(EditAnywhere)
	UStaticMesh* ResourceMesh;
};
