// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

class UButton;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class FLYINGSAWS_API UMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual bool Initialize() override;

private:

	class APlayerCharacter* PlayerRef;
	UFUNCTION(BlueprintCallable)
	void StartGame();
	UFUNCTION(BlueprintCallable)
	void QuitGame();

	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StartGameText;
	UPROPERTY(meta = (BindWidget))
	UImage* StartGameFrame;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuitGameText;
	UPROPERTY(meta = (BindWidget))
	UImage* QuitGameFrame;

	UPROPERTY(EditAnywhere)
	USoundBase* ButtonClickSound;
};
