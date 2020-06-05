// Fill out your copyright notice in the Description page of Project Settings.


#include "PaydayPrototypePlayerController.h"

void APaydayPrototypePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode( FInputModeGameOnly() );
}
