// Fill out your copyright notice in the Description page of Project Settings.


#include "Drum.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
ADrum::ADrum()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DrumMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DrumMesh"));
	RootComponent = DrumMesh;
	ArrowComponents.SetNum(8);
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Drum Audio"));

	for (int i = 0; i < 8; i++)
	{
		FString ArrowName = FString::Printf(TEXT("Arrow_%d"), i + 1);
		ArrowComponents[i] = CreateDefaultSubobject<UArrowComponent>(*ArrowName);
		ArrowComponents[i]->SetupAttachment(DrumMesh);
		ArrowComponents[i]->SetRelativeScale3D(FVector(3, 3, 3));
		ArrowComponents[i]->SetRelativeRotation(FRotator(0 + (i * 45), 0, 0));
	}
}

// Called when the game starts or when spawned
void ADrum::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADrum::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ADrum::RandTargetRotationCount()
{
	if (ActorHasTag(TEXT("Drum_1")))
	{
		return FMath::RandRange(8, 16);
	}
	else if (ActorHasTag(TEXT("Drum_2")))
	{
		return FMath::RandRange(16, 24);
	}
	else
	{
		return FMath::RandRange(24, 32);
	}
}

void ADrum::RotateDrum()
{
	if (!bIsRotating)
	{
		bIsRotating = true;
		RotationCount = 0;
		TargetRotationCount = 3 * RandTargetRotationCount();
	}
	if (bIsRotating)
	{
		DrumMesh->AddLocalRotation(UppdateRot * -1);
		RotationCount++;
		if (RotationCount >= TargetRotationCount)
		{
			GetWorldTimerManager().ClearTimer(DrumRotateTimer);
			bIsRotating = false;
			AudioComponent->Stop();
			if (ActorHasTag(TEXT("Drum_3")))
			{
				OnFinishedRotation.Broadcast();
			}
		}
	}
}

void ADrum::HandlePulled()
{
	GetWorldTimerManager().SetTimer(DrumRotateTimer, this, &ADrum::RotateDrum, DrumUppdateTime, true);
	AudioComponent->SetSound(DrumRotateSound);
	float RandomPitch = FMath::FRandRange(1.f, 1.05f);
	AudioComponent->SetPitchMultiplier(RandomPitch);
	AudioComponent->Play();
}

EDrumResult ADrum::DrumResult()
{
	for (int i = 0; i < 8; i++)
	{
		FVector ArrowForward = ArrowComponents[i]->GetForwardVector();
		if (ArrowForward.Z > 0.9f)
		{
			switch (i)
			{
			case 3:
			case 5:
			case 7:
				CurrentDrumResult = EDrumResult::Ogor;
				break;
			case 0:
			case 4:
				CurrentDrumResult = EDrumResult::Wisnie;
				break;
			case 1:
			case 6:
				CurrentDrumResult = EDrumResult::Paluch;
				break;
			case 2:
				CurrentDrumResult = EDrumResult::Korona;
			}
		}
	}
	return CurrentDrumResult;
}