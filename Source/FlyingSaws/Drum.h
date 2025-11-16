// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Drum.generated.h"

UENUM()
enum class EDrumResult : uint8
{
	Ogor		UMETA(DisplayName = "Ogor"),
	Wisnie		UMETA(DisplayName = "Wisnie"),
	Korona		UMETA(DisplayName = "Korona"),
	Paluch		UMETA(DisplayName = "Paluch"),
};

DECLARE_MULTICAST_DELEGATE(FFinishedRotation);

UCLASS()
class FLYINGSAWS_API ADrum : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADrum();

	UFUNCTION()
	void HandlePulled();

	UFUNCTION()
	EDrumResult DrumResult();

	FFinishedRotation OnFinishedRotation;

private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DrumMesh;
	UPROPERTY(VisibleAnywhere)
	TArray <class UArrowComponent*> ArrowComponents;

	UFUNCTION()
	void RotateDrum();
	UPROPERTY()
	FRotator TargetRot;
	bool bIsRotating;

	FTimerHandle DrumRotateTimer;
	UPROPERTY(EditDefaultsOnly)
	FRotator UppdateRot;
	UPROPERTY(EditDefaultsOnly, Category = "Drum")
	float DrumUppdateTime;
	int RotationCount;
	UPROPERTY(VisibleAnywhere)
	int TargetRotationCount;
	int RandTargetRotationCount();

	UPROPERTY(visibleAnywhere)
	EDrumResult CurrentDrumResult;

	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioComponent;
	UPROPERTY(EditAnywhere)
	USoundBase* DrumRotateSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
