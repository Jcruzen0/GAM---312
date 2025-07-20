// Fill out your copyright notice in the Description page of Project Settings.


#include "SG_BuildingPart.h"

// Sets default values
ASG_BuildingPart::ASG_BuildingPart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	PivotArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Pivot Arrow"));

	RootComponent = PivotArrow;
	MeshComp->SetupAttachment(PivotArrow);
}

// Called when the game starts or when spawned
void ASG_BuildingPart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASG_BuildingPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

