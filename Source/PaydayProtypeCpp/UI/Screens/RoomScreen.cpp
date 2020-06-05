// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomScreen.h"
#include "../../Core/DemoRoomGameMode.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PaydayProtypeCpp/Online/CoopGameSession.h"
#include "PaydayProtypeCpp/PaydayGameInstance.h"

void URoomScreen::NativeConstruct()
{
	Super::NativeConstruct();

	// Set default focus button
	if( CreateSessionButton )
	{
		CreateSessionButton->SetKeyboardFocus();
	}

	// Bind UI Buttons Callbacks
	CreateSessionButton->OnClicked.AddDynamic( this, &URoomScreen::OnCreateSessionClicked );
	SearchLanButton->OnClicked.AddDynamic( this, &URoomScreen::OnSearchSessionClicked );
	DestroySessionButton->OnClicked.AddDynamic( this, &URoomScreen::OnDestroySessionClicked );

	// Make demo cloned room info components to the scoll box
	//for( int32 i = 0; i < 30; i++ )
	//{
	//	URoomInfoComponent* roomInfoComponent = Cast<URoomInfoComponent>( CreateWidget( GetWorld(), RoomInfoComponentClass ) );
	//	if( roomInfoComponent )
	//	{
	//		roomInfoComponent->SetRoomInfo( i, FString::Printf( TEXT( "Room-%i" ), i ) );
	//		SearchResultContainer->AddChild( roomInfoComponent );
	//		aRoomInfoComponents.Add( roomInfoComponent );
	//	}
	//}
}

void URoomScreen::OnCreateSessionClicked()
{
	GEngine->AddOnScreenDebugMessage( -1, 2.0f, FColor::Green, TEXT( "Start creating session" ) );
	APlayerController* pc = GetOwningPlayer();
	if( pc )
	{
		ADemoRoomGameMode* targetGameMode = Cast<ADemoRoomGameMode>( GetWorld()->GetAuthGameMode() );
		if( targetGameMode )
		{
			targetGameMode->CreateRoom( 0 );
		}
	}
}

void URoomScreen::OnSearchSessionClicked()
{
	GEngine->AddOnScreenDebugMessage( -1, 2.0f, FColor::Green, TEXT( "Start searching lan session" ) );
	APlayerController* pc = GetOwningPlayer();
	if( pc )
	{
		ADemoRoomGameMode* targetGameMode = Cast<ADemoRoomGameMode>( GetWorld()->GetAuthGameMode() );
		if( targetGameMode )
		{
			targetGameMode->FindRooms();
		}
	}
}

void URoomScreen::OnDestroySessionClicked()
{
	GEngine->AddOnScreenDebugMessage( -1, 2.0f, FColor::Green, TEXT( "Start destroying self existing session" ) );
	APlayerController* pc = GetOwningPlayer();
	if( pc )
	{
		ADemoRoomGameMode* targetGameMode = Cast<ADemoRoomGameMode>( GetWorld()->GetAuthGameMode() );
		if( targetGameMode )
		{
			targetGameMode->DestroyExistingRoom();
		}
	}
}

void URoomScreen::ResetServerList()
{
	for( UWidget* widget : aRoomInfoComponents )
	{
		SearchResultContainer->RemoveChild( widget );
	}
	aRoomInfoComponents.Empty();
}

void URoomScreen::AddServerToList( int32 iRoomIndex, FString strServerName, int32 iPing )
{
	URoomInfoComponent* roomInfoComponent = Cast<URoomInfoComponent>( CreateWidget( GetWorld(), RoomInfoComponentClass ) );
	roomInfoComponent->SetRoomInfo( iRoomIndex, strServerName, iPing );
	SearchResultContainer->AddChild( roomInfoComponent );
	aRoomInfoComponents.Add( roomInfoComponent );
}