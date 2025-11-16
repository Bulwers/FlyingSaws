// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "PlayerCharacter.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

bool UMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	return true;
}

void UMenu::StartGame()
{
	PlayerRef->MoveCameraToGameView();
	UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickSound);
}

void UMenu::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerRef->Controller, EQuitPreference::Quit, false);
	UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickSound);
}