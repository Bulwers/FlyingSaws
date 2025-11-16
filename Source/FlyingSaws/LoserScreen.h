// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoserScreen.generated.h"

class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class FLYINGSAWS_API ULoserScreen : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateGold(int NewGoldAmount);

private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LoseText;
	UPROPERTY(meta = (BindWidget))
	UImage* LoseFrame;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GoldAmountText;
	UPROPERTY(meta = (BindWidget))
	UImage* GoldCountFrame;
	int PlayerGold;
};
