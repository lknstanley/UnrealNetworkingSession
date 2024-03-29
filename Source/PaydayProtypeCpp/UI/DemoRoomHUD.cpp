// Fill out your copyright notice in the Description page of Project Settings.

#include "DemoRoomHUD.h"

#include "Engine/Engine.h"

void ADemoRoomHUD::BeginPlay()
{
	Super::BeginPlay();

	// Init the UI
	CreateDemoRoomWidget();
}

void ADemoRoomHUD::SetServerList( TArray<FOnlineSessionSearchResult> aNewServerList )
{
	aServerList = aNewServerList;

	GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::Red, TEXT( "HI" ) );
	DemoScreen->ResetServerList();

	for( int32 i = 0; i < aNewServerList.Num(); i++ )
	{
		DemoScreen->AddServerToList( 
			i, // The index of this server in the list
			aNewServerList[ i ].Session.OwningUserName,  // Server Name
			aNewServerList[ i ].PingInMs, // Server Ping
			aNewServerList[ i ].Session.SessionSettings.NumPublicConnections, // Max Connection
			aNewServerList[i].Session.NumOpenPublicConnections // Current connected public connection count
		);
	}
	
}

void ADemoRoomHUD::CreateDemoRoomWidget()
{
	// Generate demo room screen to the viewport
	if( DemoScreenClass )
	{
		DemoScreen = Cast<URoomScreen>( CreateWidget( GetWorld(), DemoScreenClass ) );
		if( DemoScreen )
		{
			DemoScreen->AddToViewport();
		}
	}
}

void ADemoRoomHUD::UpdateServerList()
{
	for( int32 i = 0; i < aServerList.Num(); i++ )
	{
		GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::Red, TEXT( "count" ) );
	}
}
