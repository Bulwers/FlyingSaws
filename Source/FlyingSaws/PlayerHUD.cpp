// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void UPlayerHUD::UpdateGold(int NewGoldAmount)
{
	PlayerGold = NewGoldAmount;
	GoldAmountText->SetText(FText::AsNumber(PlayerGold));
}

void UPlayerHUD::UpdateFingersCut(int NewFingersCut)
{
	PlayerFingersCut = NewFingersCut;
	FingersCutText->SetText(FText::AsNumber(PlayerFingersCut));
}