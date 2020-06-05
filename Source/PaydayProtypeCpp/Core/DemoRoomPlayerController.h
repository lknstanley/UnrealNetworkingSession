// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DemoRoomPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PAYDAYPROTYPECPP_API ADemoRoomPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
};
