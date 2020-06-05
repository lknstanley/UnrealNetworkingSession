// Fill out your copyright notice in the Description page of Project Settings.


#include "PaydayGameInstance.h"
#include "Core/DemoRoomGameMode.h"
#include "Engine/Engine.h"
#include "UI/DemoRoomHUD.h"

void UPaydayGameInstance::CreateRoom( int32 HostingPlayerId )
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

			// Create Session
			bool bResult = pOnlineSession->CreateSession( 0, "Payday_Clone", *HostSettings );
			if( bResult )
			{
				GEngine->AddOnScreenDebugMessage( -1, 2.0f, FColor::Red, TEXT( "Succeed" ) );
			}
			else
			{
				GEngine->AddOnScreenDebugMessage( -1, 2.0f, FColor::Red, TEXT( "Failed" ) );
			}
		}
	}
}

void UPaydayGameInstance::FindRooms()
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

void UPaydayGameInstance::JoinRoom()
{
}

void UPaydayGameInstance::OnCreateSessionComplete( FName strSessionName, bool bWasSuccessful )
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

void UPaydayGameInstance::OnFindSessionsComplete( bool bWasSuccessful )
{
	GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::Red, TEXT( "ADemoRoomGameMode - OnFindSessionsComplete" ) );
	IOnlineSubsystem* pOnlineSubsystem = IOnlineSubsystem::Get();
	if( pOnlineSubsystem )
	{
		IOnlineSessionPtr pOnlineSession = pOnlineSubsystem->GetSessionInterface();

		if( pOnlineSession )
		{
			pOnlineSession->ClearOnFindSessionsCompleteDelegate_Handle( OnFindSessionsCompleteDelegateHandle );

			ADemoRoomHUD* targetHUD = Cast<ADemoRoomHUD>( GetWorld()->GetFirstPlayerController()->GetHUD() );
			if( targetHUD )
			{
				targetHUD->SetServerList( SearchSettings->SearchResults );
			}
		}
	}
}