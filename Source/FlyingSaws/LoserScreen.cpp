// Fill out your copyright notice in the Description page of Project Settings.


#include "LoserScreen.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void ULoserScreen::UpdateGold(int NewGoldAmount)
{
	PlayerGold = NewGoldAmount;
	GoldAmountText->SetText(FText::AsNumber(PlayerGold));
}