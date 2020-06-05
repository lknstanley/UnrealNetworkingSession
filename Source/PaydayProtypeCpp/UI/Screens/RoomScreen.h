// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "PaydayProtypeCpp/UI/Components/RoomInfoComponent.h"
#include "RoomScreen.generated.h"

/**
 * 
 */
UCLASS()
class PAYDAYPROTYPECPP_API URoomScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/*
	 * UserWidget Virtual Methods
	 */
	virtual void NativeConstruct() override;

	/*
	 * UI References
	 */
	UPROPERTY( meta = ( BindWidget ) )
		UButton* CreateSessionButton;
	UPROPERTY( meta = ( BindWidget ) )
		UButton* SearchLanButton;
	UPROPERTY( meta = ( BindWidget ) )
		UButton* DestroySessionButton;
	UPROPERTY( meta = ( BindWidget ) )
		UScrollBox* SearchResultContainer;

	// Room Info Component Class Reference
	UPROPERTY( EditAnywhere, Category = "UI References Settings", DisplayName = "Room Info Component" )
		TSubclassOf<URoomInfoComponent> RoomInfoComponentClass;
	TArray<URoomInfoComponent*> aRoomInfoComponents;

	/*
	 * Create/Search Session Callbacks
	 */
	UFUNCTION()
		void OnCreateSessionClicked();
	UFUNCTION()
		void OnSearchSessionClicked();
	UFUNCTION()
		void OnDestroySessionClicked();

	/*
	 * Interfaces
	 */
	void ResetServerList();
	void AddServerToList( int32 iRoomIndex, FString strServerName, int32 iPing );
};