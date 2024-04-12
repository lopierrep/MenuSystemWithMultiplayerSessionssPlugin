// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState)
	{
		int32 PlayerCount = GameState.Get()->PlayerArray.Num();
		GEngine->AddOnScreenDebugMessage(1, 500.0f, FColor::Yellow, FString::Printf(TEXT("Player count %d"), PlayerCount));

		APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
		if (PlayerState)
		{
			FString PlayerName = PlayerState->GetPlayerName();
			GEngine->AddOnScreenDebugMessage(-1, 500.0f, FColor::Cyan, FString::Printf(TEXT("%s has joined the game"), *PlayerName));
		}
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	int32 PlayerCount = GameState.Get()->PlayerArray.Num();
	GEngine->AddOnScreenDebugMessage(1, 500.0f, FColor::Yellow,
	                                 FString::Printf(TEXT("Player count %d"), PlayerCount - 1));
	
	APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>();
	if (PlayerState)
	{
		FString PlayerName = PlayerState->GetPlayerName();
		GEngine->AddOnScreenDebugMessage(-1, 500.0f, FColor::Cyan, FString::Printf(TEXT("%s has exited the game"), *PlayerName));
	}
}
