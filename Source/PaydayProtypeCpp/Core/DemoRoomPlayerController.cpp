// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoRoomPlayerController.h"

void ADemoRoomPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode( FInputModeUIOnly() );
}
