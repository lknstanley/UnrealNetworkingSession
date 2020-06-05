// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PaydayPrototypePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PAYDAYPROTYPECPP_API APaydayPrototypePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
};
