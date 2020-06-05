// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Screens/RoomScreen.h"
#include "Online.h"
#include "DemoRoomHUD.generated.h"

/**
 * 
 */
UCLASS()
class PAYDAYPROTYPECPP_API ADemoRoomHUD : public AHUD
{
	GENERATED_BODY()

	/*
	 * Internal Interfaces
	 */
	void CreateDemoRoomWidget();
	void UpdateServerList();

	TArray<FOnlineSessionSearchResult> aServerList;
	
public:
		
	/*
	 * HUD Class Virtual Methods
	 */
	virtual void BeginPlay() override;
	

	UPROPERTY( EditAnywhere, Category = "UI Settings" )
	TSubclassOf<URoomScreen> DemoScreenClass;
	UPROPERTY()
	URoomScreen* DemoScreen;

	// Interface for session to update server list
	void SetServerList( TArray<FOnlineSessionSearchResult> aNewServerList );
	
};
