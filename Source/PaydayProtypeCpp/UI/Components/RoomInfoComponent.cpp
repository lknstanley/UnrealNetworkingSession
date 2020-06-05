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

void URoomInfoComponent::SetRoomInfo( int32 iNewRoomId, FString strNewOwnerName, int32 iPingInMs )
{
	iRoomId = iNewRoomId;
	strOwnerName = strNewOwnerName;

	RoomOwnerName->SetText( FText::FromString( strNewOwnerName ) );
	RoomStatus->SetText( FText::FromString( FString::FromInt( iPingInMs ) ) );
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