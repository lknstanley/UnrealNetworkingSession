// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomInfoComponent.h"
#include "../../Core/DemoRoomGameMode.h"
#include "Engine/Engine.h"

void URoomInfoComponent::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind the button callback
	if( MainButton )
	{
		MainButton->OnClicked.AddDynamic( this, &URoomInfoComponent::OnClicked );
	}
}

void URoomInfoComponent::SetRoomInfo( int32 iNewRoomId, FString strNewOwnerName, int32 iPingInMs, int32 iNumOfMaxConnection, int32 iCurrentAvailableConnection )
{
	iRoomId = iNewRoomId;
	strOwnerName = strNewOwnerName;

	GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::Blue, FString::Printf( TEXT( "Max Connection: %d" ), iNumOfMaxConnection ) );
	GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::Blue, FString::Printf( TEXT( "Ava Slot: %d" ), iCurrentAvailableConnection ) );
	
	RoomOwnerName->SetText( FText::FromString( strNewOwnerName ) );
	RoomStatus->SetText( FText::FromString( FString::Printf( TEXT( "%dms" ),  iPingInMs ) ) );
	RoomPlayerCount->SetText( FText::FromString( FString::Printf( TEXT( "%d/%d" ), iNumOfMaxConnection - iCurrentAvailableConnection, iNumOfMaxConnection ) ) );
}

void URoomInfoComponent::OnClicked()
{
	GEngine->AddOnScreenDebugMessage( -1, 2.0f, FColor::Emerald, FString::Printf( TEXT( "Clicked RoomId: %i, Name: %s" ), iRoomId, *strOwnerName ) );
	
	ADemoRoomGameMode* targetGameMode = Cast<ADemoRoomGameMode>( GetWorld()->GetAuthGameMode() );
	if( targetGameMode )
	{
		targetGameMode->JoinRoom( 0, iRoomId );
	}
}