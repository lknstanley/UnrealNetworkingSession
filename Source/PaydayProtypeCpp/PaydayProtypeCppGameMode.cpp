// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PaydayProtypeCppGameMode.h"

#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "PaydayProtypeCppHUD.h"
#include "PaydayProtypeCppCharacter.h"
#include "UObject/ConstructorHelpers.h"

APaydayProtypeCppGameMode::APaydayProtypeCppGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = APaydayProtypeCppHUD::StaticClass();
}

void APaydayProtypeCppGameMode::PreLogin( const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage )
{
	Super::PreLogin( Options, Address, UniqueId, ErrorMessage );
	GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::Red, TEXT( "APaydayProtypeCppGameMode - PreLogin" ) );
}

void APaydayProtypeCppGameMode::PostLogin( APlayerController* NewPlayer )
{
	Super::PostLogin( NewPlayer );
	GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::Red, TEXT( "APaydayProtypeCppGameMode - PostLogin" ) );
}

void APaydayProtypeCppGameMode::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::Red, TEXT( "APaydayProtypeCppGameMode - BeginPlay" ) );
}
