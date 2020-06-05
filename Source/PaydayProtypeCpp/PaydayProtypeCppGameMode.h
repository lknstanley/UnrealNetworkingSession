// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PaydayProtypeCppGameMode.generated.h"

UCLASS(minimalapi)
class APaydayProtypeCppGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APaydayProtypeCppGameMode();

	virtual void PreLogin( const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage ) override;
	virtual void PostLogin( APlayerController* NewPlayer ) override;
	virtual void BeginPlay() override;
};



