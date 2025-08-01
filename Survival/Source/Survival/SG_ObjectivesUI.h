// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_ObjectivesUI.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API USG_ObjectivesUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateMatObjective(float matCollected);
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBuildObjective(float builtObject);	
	
};
