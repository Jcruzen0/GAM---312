// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API USG_PlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBars(float aHealth, float aHunger, float aStamina);
};
