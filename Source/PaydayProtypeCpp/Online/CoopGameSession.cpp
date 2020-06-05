// Fill out your copyright notice in the Description page of Project Settings.


#include "CoopGameSession.h"

#include "Engine/Engine.h"
#include "PaydayProtypeCpp/Core/DemoRoomGameMode.h"
#include "PaydayProtypeCpp/UI/DemoRoomHUD.h"

ACoopGameSession::ACoopGameSession()
{
	// Bind Session Callbacks
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject( this, &ACoopGameSession::OnCreateSessionComplete );
	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject( this, &ACoopGameSession::OnFindSessionsComplete );
}

void ACoopGameSession::CreateRoom( int32 HostingPlayerId )
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

void ACoopGameSession::FindRooms()
{
}

void ACoopGameSession::JoinRoom()
{
}

void ACoopGameSession::OnCreateSessionComplete( FName strSessionName, bool bWasSuccessful )
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
				// Navigate to the main gameplay level
				ADemoRoomGameMode* targetGameMode = Cast<ADemoRoomGameMode>( GetWorld()->GetAuthGameMode() );
				if( targetGameMode )
				{
					targetGameMode->NavigateToLevel( "FirstPersonExampleMap" );
				}
			}
			
		}

	}
}

void ACoopGameSession::OnFindSessionsComplete(bool bWasSuccessful)
{
	IOnlineSubsystem* pOnlineSubsystem = IOnlineSubsystem::Get();
	if( pOnlineSubsystem )
	{
		IOnlineSessionPtr pOnlineSession = pOnlineSubsystem->GetSessionInterface();

		if( pOnlineSession )
		{
			ADemoRoomHUD* targetHUD = Cast<ADemoRoomHUD>( GetWorld()->GetFirstPlayerController()->GetHUD() );
			if( targetHUD )
			{
				targetHUD->SetServerList( SearchSettings->SearchResults );
			}
		}
	}
}
