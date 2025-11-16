// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FLYINGSAWS_API APlayerCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

	void CutFinger();

	void AddGold(int Amount);
	void RemoveGold();

	void MoveCameraToMenuView();
	void MoveCameraToGameView();

	class APlayerController* Controller;

private:

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	FVector MenuCameraPosition;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	FRotator MenuCameraRotation;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	FVector GameCameraPosition;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	FRotator GameCameraRotation;

	FTimerHandle CameraMoveTimer;
	void GameMenuCameraMove();
	void StartGameCameraMove();
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	int CameraMoveSpeedLoc;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	int CameraMoveSpeedRot;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float CameraUpdateTime;


	class UMenu* MenuWidget;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMenu> MenuWidgetClass;

	class UPlayerHUD* PlayerHUDWidget;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UPlayerHUD> PlayerHUDWidgetClass;

	class ULoserScreen* LoserScreenWidget;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<ULoserScreen> LoserScreenWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int StartingGoldAmount;
	UPROPERTY(VisibleAnywhere)
	int CurrentGoldAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int MaxFingersCount;
	UPROPERTY(VisibleAnywhere, Category = "Stats")
	int CurrentFingersCount;

	UAudioComponent* AudioComponent;
	UPROPERTY(EditAnywhere)
	USoundBase* BackgroundMusic;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
