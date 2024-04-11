// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "Components/Button.h"
#include "MultiplayerSessions/Subsystem/MultiplayerSessionsSubsystem.h"

void UMenu::MenuSetup()
{
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	UWorld* World = GetWorld();
	if (!World) return;
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}		
	}
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}
	
}

bool UMenu::Initialize()
{
	if (!Super::Initialize()) return false;
	if (!HostButton) return false;
	if (!JoinButton) return false;

	HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	
	return true;
}

void UMenu::HostButtonClicked()
{
	if (!GEngine) return;	
	GEngine->AddOnScreenDebugMessage(-1, 500.0f, FColor::Yellow, FString::Printf(TEXT("HOST BUTTON CLICKED")));
	
	if (!MultiplayerSessionsSubsystem) return;
	MultiplayerSessionsSubsystem->CreateSession(4, FString("FreeForAll"));
}

void UMenu::JoinButtonClicked()
{
	if (!GEngine) return;
	GEngine->AddOnScreenDebugMessage(-1, 500.0f, FColor::Yellow, FString::Printf(TEXT("JOIN BUTTON CLICKED")));	
}
