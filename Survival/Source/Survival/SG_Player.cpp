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

	BuildingArray.SetNum(3);
	ResourcesArray.SetNum(3);
	ResourcesNameArray.Add(TEXT("Wood"));
	ResourcesNameArray.Add(TEXT("Stone"));
	ResourcesNameArray.Add(TEXT("Berry"));
}

// Called when the game starts or when spaw
// ned
void ASG_Player::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle StatsTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(StatsTimerHandle, this, &ASG_Player::DecreaseStats, 2.0f, true);

	if (ObjectiveUI)
	{
		// Initialize our stats to 0
		ObjectiveUI->UpdateBuildObjective(0.0f);
		ObjectiveUI->UpdateMatObjective(0.0f);
	}

}

// Called every frame
void ASG_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerHUD->UpdateBars(Health, Hunger, Stamina);

	if (bIsBuilding)
	{
		if (BuildingPart)
		{
			FVector StartLocation = PlayerCamComp->GetComponentLocation();
			FVector Direction = PlayerCamComp->GetForwardVector() * 400.0;
			FVector EndLocation = StartLocation + Direction;
			BuildingPart->SetActorLocation(EndLocation);
		}
	}
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

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ASG_Player::FindObject);
	PlayerInputComponent->BindAction("RotPart", IE_Pressed, this, &ASG_Player::RotateBuilding);
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

// Called to perform a line trace and interact with resource objects in front of the player
void ASG_Player::FindObject()
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCamComp->GetComponentLocation();
	FVector Direction = PlayerCamComp->GetForwardVector() * 800.0f;
	FVector EndLocation = StartLocation + Direction;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnFaceIndex = true;

	if (!bIsBuilding)
	{
		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams))
		{
			AResource_M* HitResource = Cast<AResource_M>(HitResult.GetActor());
			if (Stamina > 5.0f)
			{
				if (HitResource)
				{
					FString HitName = HitResource->ResourceName;
					int ResourceValue = HitResource->ResourceAmount;

					// Reduce resource's total amount
					HitResource->TotalResource -= ResourceValue;

					if (HitResource->TotalResource > ResourceValue)
					{
						GiveResource(ResourceValue, HitName);

						// Updated Materials collected objective
						MaterialsCollected += ResourceValue;
						ObjectiveUI->UpdateMatObjective(MaterialsCollected);

						check(GEngine != nullptr);
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Collected"));
					}
					else
					{
						HitResource->Destroy();
						check(GEngine != nullptr);
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Depleted"));
					}
				}
			}
		}
	}
	else
	{
		bIsBuilding = false;
		BuiltObjectives += 1.0f;
		ObjectiveUI->UpdateBuildObjective(BuiltObjectives);
	}
}

// Sets the player's health, preventing it from exceeding 100
void ASG_Player::SetHealth(float Value)
{
	if (Health + Value < 100)
	{
		Health += Value;
	}
}

// Sets the player's hunger, preventing it from exceeding 100
void ASG_Player::SetHunger(float Value)
{
	if (Hunger + Value < 100)
	{
		Hunger += Value;
	}
}

// Sets the player's stamina, preventing it from exceeding 100
void ASG_Player::SetStamina(float Value)
{
	if (Stamina + Value < 100)
	{
		Stamina += Value;
	}

		if (Stamina < 0)
		Stamina = 0;
}

// Decreases hunger over time; if hunger reaches zero, reduces health
void ASG_Player::DecreaseStats()
{
	if (Hunger > 0)
	{
		SetHunger(-1.0f);
	}

	SetStamina(-5.0f);

	if (Hunger <= 0)
	{
		SetHealth(-3.0f);
	}
}

// Adds a specified resource amount to the player's inventory array
void ASG_Player::GiveResource(float Value, FString ResourceType)
{
	if (ResourceType == TEXT("Wood"))
	{
		ResourcesArray[0] += Value;
	}
	else if (ResourceType == TEXT("Stone"))
	{
		ResourcesArray[1] += Value;
	}
	else if (ResourceType == TEXT("Berry"))
	{
		ResourcesArray[2] += Value;
	}

	SetStamina(-5.0f);
	
}

void ASG_Player::UpdateResources(float woodAmount, float stoneAmount, FString buildingObject)
{
	if (woodAmount <= ResourcesArray[0])
	{
		if (stoneAmount <= ResourcesArray[1])
		{
			ResourcesArray[0] -= woodAmount;
			ResourcesArray[1] -= stoneAmount;

			if (buildingObject == TEXT("Wall"))
			{
				BuildingArray[0] += 1;
			}

			if (buildingObject == TEXT("Floor"))
			{
				BuildingArray[1] += 1;
			}

			if (buildingObject == TEXT("Ceiling"))
			{
				BuildingArray[2] += 1;
			}
		}
	}
}

void ASG_Player::SpawnBuilding(int buildingID, bool& isSuccess)
{
	if (!bIsBuilding)
	{
		if (BuildingArray[buildingID] >= 1)
		{
			bIsBuilding = true;
			FActorSpawnParameters SpawnParams;
			FVector StartLocation = PlayerCamComp->GetComponentLocation();
			FVector Direction = PlayerCamComp->GetForwardVector() * 400.0;
			FVector EndLocation = StartLocation + Direction;
			FRotator myRot(0,0,0);

			BuildingArray[buildingID] -= 1;

			BuildingPart = GetWorld()->SpawnActor<ASG_BuildingPart>(BuildingPartClass, EndLocation, myRot, SpawnParams);

			isSuccess = true;

		}
		else
		{
			isSuccess = false;
		}
	}
}

void ASG_Player::RotateBuilding()
{
	if (bIsBuilding)
	{
		BuildingPart->AddActorWorldRotation(FRotator(0,90,0));
	}
}
