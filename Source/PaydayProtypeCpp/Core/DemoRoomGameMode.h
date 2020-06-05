// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Online.h"
#include "DemoRoomGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PAYDAYPROTYPECPP_API ADemoRoomGameMode : public AGameMode
{
	GENERATED_BODY()

	// Game Session Settings
	TSharedPtr<FOnlineSessionSearch> SearchSettings;
	TSharedPtr<FOnlineSessionSettings> HostSettings;

	// Create Session Handler & Delegate
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;

	FDelegateHandle OnStartSessionCompleteDelegateHandle;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	FDelegateHandle OnDestroySessionCompleteDelegateHandle;
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;

	// Find Session Handler & Delegate
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;

	FDelegateHandle OnFindFriendSessionCompleteDelegateHandle;
	FOnFindFriendSessionCompleteDelegate OnFindFriendSessionCompleteDelegate;

	// Join Session Handler & Delegate
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	
public:

	virtual void BeginPlay() override;
	
	void NavigateToLevel( FName strLevelName );

	/*
	 * Session Manager Interfaces
	 */
	void CreateRoom( int32 HostingPlayerId );
	void FindRooms();
	void JoinRoom( int32 iJoiningPlayerId, int32 iSessionIndex );
	void DestroyExistingRoom();

	/*
	 * Session Callbacks
	 */
	void OnCreateSessionComplete( FName strSessionName, bool bWasSuccessful );
	void OnFindSessionsComplete( bool bWasSuccessful );
	void OnJoinSessionComplete( FName strSessionName, EOnJoinSessionCompleteResult::Type eResult );
};
