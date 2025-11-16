// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class FLYINGSAWS_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void UpdateGold(int NewGoldAmount);
	void UpdateFingersCut(int NewFingersCut);

protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GoldAmountText;
	UPROPERTY(meta = (BindWidget))
	UImage* GoldIconImage;
	UPROPERTY(meta = (BindWidget))
	UImage* GoldFrameImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* FingersCutText;
	UPROPERTY(meta = (BindWidget))
	UImage* FingersIconImage;

	int PlayerGold;
	int PlayerFingersCut;
};
