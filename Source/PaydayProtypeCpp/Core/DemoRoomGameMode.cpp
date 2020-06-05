// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoRoomGameMode.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"
#include "PaydayProtypeCpp/UI/DemoRoomHUD.h"
#include "GameFramework/PlayerController.h"

void ADemoRoomGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameUserSettings* pMyGameSettings = GEngine->GetGameUserSettings();
	pMyGameSettings->SetFullscreenMode( EWindowMode::Windowed );
	pMyGameSettings->SetScreenResolution( FIntPoint( 1280, 720 ) );

	// Bind Session Callbacks
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject( this, &ADemoRoomGameMode::OnCreateSessionComplete );
	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject( this, &ADemoRoomGameMode::OnFindSessionsComplete );
	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject( this, &ADemoRoomGameMode::OnJoinSessionComplete );
}

void ADemoRoomGameMode::NavigateToLevel(FName strLevelName)
{
	UGameplayStatics::OpenLevel( GetWorld(), strLevelName, true, "listen" );
}

void ADemoRoomGameMode::CreateRoom( int32 HostingPlayerId )
{
	IOnlineSubsystem* pOnlineSubsystem = IOnlineSubsystem::Get();
	if( pOnlineSubsystem )
	{
		IOnlineSessionPtr pOnlineSession = pOnlineSubsystem->GetSessionInterface();

		if( pOnlineSession )
		{

			GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::Red, TEXT( "Creating Session..." ) );

			// Create the host settings
			HostSettings = MakeShareable( new FOnlineSessionSettings() );
			HostSettings->bIsLANMatch = true;
			HostSettings->bAllowJoinInProgress = true;
			HostSettings->bUsesPresence = true;
			HostSettings->bShouldAdvertise = true;

			// Debug the LAN connection works first
			HostSettings->NumPublicConnections = 4;
			HostSettings->NumPrivateConnections = 0;

			// Bind the Complete Callback
			OnCreateSessionCompleteDelegateHandle = pOnlineSession->AddOnCreateSessionCompleteDelegate_Handle( OnCreateSessionCompleteDelegate );

			// Get Local First Player Controller
			FUniqueNetIdRepl wrapperNetId = GetWorld()->GetFirstLocalPlayerFromController()->GetPreferredUniqueNetId();
			
			// Create Session
			bool bResult = pOnlineSession->CreateSession( *wrapperNetId.GetUniqueNetId(), "Payday_Clone", *HostSettings );
			if( bResult )
			{
				GEngine->AddOnScreenDebugMessage( -1, 2.0f, FColor::Red, TEXT( "Succeed" ) );
			}
			else
			{
				GEngine->AddOnScreenDebugMessage( -1, 2.0f, FColor::Red, TEXT( "Failed" ) );
				pOnlineSession->DestroySession( "Payday_Clone" );
			}
		}
	}
}

void ADemoRoomGameMode::FindRooms()
{
	IOnlineSubsystem* pOnlineSubsystem = IOnlineSubsystem::Get();
	if( pOnlineSubsystem )
	{
		IOnlineSessionPtr pOnlineSession = pOnlineSubsystem->GetSessionInterface();

		if( pOnlineSession )
		{
			GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::Red, TEXT( "Searching Session..." ) );

			// Make search settings
			SearchSettings = MakeShareable( new FOnlineSessionSearch() );
			SearchSettings->bIsLanQuery = true;
			SearchSettings->MaxSearchResults = 10;
			SearchSettings->PingBucketSize = 50;

			// Bind the search complete callback
			OnFindSessionsCompleteDelegateHandle = pOnlineSession->AddOnFindSessionsCompleteDelegate_Handle( OnFindSessionsCompleteDelegate );

			// Find sessions
			pOnlineSession->FindSessions( 0, SearchSettings.ToSharedRef() );
		}
	}
}

void ADemoRoomGameMode::JoinRoom( int32 iJoiningPlayerId, int32 iSessionIndex )
{
	IOnlineSubsystem* pOnlineSubsystem = IOnlineSubsystem::Get();
	if( pOnlineSubsystem )
	{
		IOnlineSessionPtr pOnlineSession = pOnlineSubsystem->GetSessionInterface();

		if( pOnlineSession )
		{
			GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::Red, TEXT( "Joining Session..." ) );

			// Bind Join Session Callback Function
			OnJoinSessionCompleteDelegateHandle = pOnlineSession->AddOnJoinSessionCompleteDelegate_Handle( OnJoinSessionCompleteDelegate );

			// Get Local First Player Controller
			FUniqueNetIdRepl wrapperNetId = GetWorld()->GetFirstLocalPlayerFromController()->GetPreferredUniqueNetId();
			
			// Join Session
			bool bResult = pOnlineSession->JoinSession( *wrapperNetId.GetUniqueNetId(), "Payday_Clone", SearchSettings->SearchResults[ iSessionIndex ] );

			if( bResult )
			{
				GEngine->AddOnScreenDebugMessage( -1, 10.0f, FColor::Red, TEXT( "Succeed to join session" ) );
			}
			else
			{
				GEngine->AddOnScreenDebugMessage( -1, 10.0f, FColor::Red, TEXT( "Failed to join session" ) );
			}
		}
	}
}

void ADemoRoomGameMode::DestroyExistingRoom()
{
	IOnlineSubsystem* pOnlineSubsystem = IOnlineSubsystem::Get();
	if( pOnlineSubsystem )
	{
		IOnlineSessionPtr pOnlineSession = pOnlineSubsystem->GetSessionInterface();

		if( pOnlineSession )
		{
			// Try to destroy self session to prevent duplicated server
			pOnlineSession->DestroySession( "Payday_Clone" );
		}
	}
}

void ADemoRoomGameMode::OnCreateSessionComplete( FName strSessionName, bool bWasSuccessful )
{
	GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::Red, FString::Printf( TEXT( "Successful: %d, Session Name: %s" ), bWasSuccessful ? 1 : 0, *strSessionName.ToString() ) );
	IOnlineSubsystem* pOnlineSubsystem = IOnlineSubsystem::Get();
	if( pOnlineSubsystem )
	{
		IOnlineSessionPtr pOnlineSession = pOnlineSubsystem->GetSessionInterface();

		if( pOnlineSession )
		{
			pOnlineSession->ClearOnCreateSessionCompleteDelegate_Handle( OnCreateSessionCompleteDelegateHandle );


			// Try to destroy the session if it failed
			if( !bWasSuccessful )
			{
				pOnlineSession->DestroySession( "Payday_Clone" );
			}
			else
			{
				ADemoRoomGameMode* targetGameMode = Cast<ADemoRoomGameMode>( GetWorld()->GetAuthGameMode() );
				if( targetGameMode )
				{
					targetGameMode->NavigateToLevel( "FirstPersonExampleMap" );
				}
			}

		}

	}
}

void ADemoRoomGameMode::OnFindSessionsComplete( bool bWasSuccessful )
{
	GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::Red, TEXT( "ADemoRoomGameMode - OnFindSessionsComplete" ) );
	IOnlineSubsystem* pOnlineSubsystem = IOnlineSubsystem::Get();
	if( pOnlineSubsystem )
	{
		IOnlineSessionPtr pOnlineSession = pOnlineSubsystem->GetSessionInterface();

		if( pOnlineSession )
		{
			// Clean the delegate to avoid duplicated callback events
			pOnlineSession->ClearOnFindSessionsCompleteDelegate_Handle( OnFindSessionsCompleteDelegateHandle );

			// Update the server list by passing the searching result to the HUD
			ADemoRoomHUD* targetHUD = Cast<ADemoRoomHUD>( GetWorld()->GetFirstPlayerController()->GetHUD() );
			if( targetHUD )
			{
				targetHUD->SetServerList( SearchSettings->SearchResults );
			}
		}
	}
}

void ADemoRoomGameMode::OnJoinSessionComplete( FName strSessionName, EOnJoinSessionCompleteResult::Type eResult )
{
	GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::Red, TEXT( "ADemoRoomGameMode - OnJoinSessionComplete" ) );
	IOnlineSubsystem* pOnlineSubsystem = IOnlineSubsystem::Get();
	if( pOnlineSubsystem )
	{
		IOnlineSessionPtr pOnlineSession = pOnlineSubsystem->GetSessionInterface();

		if( pOnlineSession )
		{
			// Clean the delegate to avoid duplicated callback events
			pOnlineSession->ClearOnJoinSessionCompleteDelegate_Handle( OnJoinSessionCompleteDelegateHandle );

			// Start navigating player to the selected online session level
			APlayerController * pLocalPlayerController = UGameplayStatics::GetPlayerController( GetWorld(), 0 );

			// A container for the engine to know where we are going to
			FString strTravelUrl;

			// Checking the First Local PlayerController is not null and the session name is match with the selected online session
			if( pLocalPlayerController && pOnlineSession->GetResolvedConnectString( strSessionName, strTravelUrl ) )
			{
				GEngine->AddOnScreenDebugMessage( -1, 10.0f, FColor::Red, TEXT( "Travel To Level" ) );
				pLocalPlayerController->ClientTravel( strTravelUrl, ETravelType::TRAVEL_Absolute );

				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, strTravelUrl );
			}
		}
	}
}
