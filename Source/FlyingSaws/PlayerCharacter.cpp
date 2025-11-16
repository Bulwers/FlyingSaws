// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerHUD.h"
#include "Menu.h"
#include "LoserScreen.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComponent;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(RootComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GameCameraPosition = CameraComponent->GetComponentLocation();
	GameCameraRotation = CameraComponent->GetComponentRotation();

	CameraComponent->SetWorldLocation(MenuCameraPosition);
	CameraComponent->SetWorldRotation(MenuCameraRotation);

	Controller = Cast<APlayerController>(GetController());
	Controller->bShowMouseCursor = true;
	Controller->bEnableClickEvents = true;
	Controller->bEnableMouseOverEvents = true;

	AudioComponent->SetSound(BackgroundMusic);
	AudioComponent->SetVolumeMultiplier(0.5f);
	AudioComponent->Play();

	PlayerHUDWidget = CreateWidget<UPlayerHUD>(GetWorld(), PlayerHUDWidgetClass);
	MenuWidget = CreateWidget<UMenu>(GetWorld(), MenuWidgetClass);
	LoserScreenWidget = CreateWidget<ULoserScreen>(GetWorld(), LoserScreenWidgetClass);

	if (MenuWidget)
	{
		MenuWidget->AddToViewport();
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void APlayerCharacter::GameMenuCameraMove()
{
	CameraComponent->SetWorldLocation(FMath::VInterpConstantTo(CameraComponent->GetComponentLocation(), MenuCameraPosition, GetWorld()->GetDeltaSeconds(), CameraMoveSpeedLoc));
	CameraComponent->SetWorldRotation(FMath::RInterpConstantTo(CameraComponent->GetComponentRotation(), MenuCameraRotation, GetWorld()->GetDeltaSeconds(), CameraMoveSpeedRot));
	if (CameraComponent->GetComponentLocation().Equals(MenuCameraPosition, 1.0f) &&
		CameraComponent->GetComponentRotation().Equals(MenuCameraRotation, 1.0f))
	{
		GetWorldTimerManager().ClearTimer(CameraMoveTimer);
	}
}

void APlayerCharacter::StartGameCameraMove()
{
	CameraComponent->SetWorldLocation(FMath::VInterpConstantTo(CameraComponent->GetComponentLocation(), GameCameraPosition, GetWorld()->GetDeltaSeconds(), CameraMoveSpeedLoc));
	CameraComponent->SetWorldRotation(FMath::RInterpConstantTo(CameraComponent->GetComponentRotation(), GameCameraRotation, GetWorld()->GetDeltaSeconds(), CameraMoveSpeedRot));
	if (CameraComponent->GetComponentLocation().Equals(GameCameraPosition, 1.0f) &&
		CameraComponent->GetComponentRotation().Equals(GameCameraRotation, 1.0f))
	{
		GetWorldTimerManager().ClearTimer(CameraMoveTimer);
	}
}

void APlayerCharacter::MoveCameraToMenuView()
{
	AudioComponent->SetVolumeMultiplier(0.5f);
	GetWorldTimerManager().SetTimer(CameraMoveTimer, this, &APlayerCharacter::GameMenuCameraMove, CameraUpdateTime, true);
	if (PlayerHUDWidget->IsInViewport())
	{
		PlayerHUDWidget->RemoveFromViewport();
	}
	if (!MenuWidget->IsInViewport())
	{
		MenuWidget->AddToViewport();
	}
}

void APlayerCharacter::MoveCameraToGameView()
{
	CurrentFingersCount = MaxFingersCount;
	CurrentGoldAmount = StartingGoldAmount;

	AudioComponent->SetVolumeMultiplier(0.25f);
	GetWorldTimerManager().SetTimer(CameraMoveTimer, this, &APlayerCharacter::StartGameCameraMove, CameraUpdateTime, true);
	if (MenuWidget->IsInViewport())
	{
		MenuWidget->RemoveFromViewport();
	}
	if (LoserScreenWidget->IsInViewport())
	{
		LoserScreenWidget->RemoveFromViewport();
	}
	if (!PlayerHUDWidget->IsInViewport())
	{
		PlayerHUDWidget->AddToViewport();
		PlayerHUDWidget->UpdateGold(StartingGoldAmount);
		PlayerHUDWidget->UpdateFingersCut(0);
	}
}

void APlayerCharacter::CutFinger()
{
	CurrentFingersCount--;
	PlayerHUDWidget->UpdateFingersCut(MaxFingersCount - CurrentFingersCount);
	if (CurrentFingersCount <= 0)
	{
		MoveCameraToMenuView();
		if (!LoserScreenWidget->IsInViewport())
		{
			LoserScreenWidget->UpdateGold(CurrentGoldAmount);
			LoserScreenWidget->AddToViewport();
		}
	}
}

void APlayerCharacter::AddGold(int Amount)
{
	CurrentGoldAmount += Amount;
	PlayerHUDWidget->UpdateGold(CurrentGoldAmount);
}

void APlayerCharacter::RemoveGold()
{
	CurrentGoldAmount--;
	PlayerHUDWidget->UpdateGold(CurrentGoldAmount);
	if (CurrentGoldAmount <= 0)
	{
		MoveCameraToMenuView();
		if (!LoserScreenWidget->IsInViewport())
		{
			LoserScreenWidget->UpdateGold(CurrentGoldAmount);
			LoserScreenWidget->AddToViewport();
		}
	}
}
