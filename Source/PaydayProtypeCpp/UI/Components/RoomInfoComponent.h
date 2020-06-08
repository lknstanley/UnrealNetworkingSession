// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "RoomInfoComponent.generated.h"

/**
 * 
 */
UCLASS()
class PAYDAYPROTYPECPP_API URoomInfoComponent : public UUserWidget
{
	GENERATED_BODY()

	// Room Info
	int32 iRoomId;
	FString strOwnerName;
	
public:

	/*
	 * User Widget Lifecycle
	 */
	virtual void NativeConstruct() override;
	
	/*
	 * UI References
	 */
	UPROPERTY( meta = ( BindWidget ) )
	UButton* MainButton;
	UPROPERTY( meta = ( BindWidget ) )
	UTextBlock* RoomOwnerName;
	UPROPERTY( meta = ( BindWidget ) )
	UTextBlock* RoomStatus;
	UPROPERTY( meta = (BindWidget) )
	UTextBlock* RoomPlayerCount;

	/*
	 * Public Interfaces
	 */
	void SetRoomInfo( int32 iNewRoomId, FString strNewOwnerName, int32 iPingInMs, int32 iNumOfMaxConnection, int32 iCurrentAvailableConnection );

	/*
	 * UI Callbacks
	 */
	UFUNCTION()
	void OnClicked();
};