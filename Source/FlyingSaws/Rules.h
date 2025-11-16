// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rules.generated.h"

UCLASS()
class FLYINGSAWS_API ARules : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARules();

private:

	FVector StartLocation;
	FRotator StartRotation;

	UPROPERTY(EditDefaultsOnly)
	FVector AddLocation;
	UPROPERTY(EditDefaultsOnly)
	FRotator AddRotation;
	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RulesMesh;

	FTimerHandle MoveTimerHandle;
	UFUNCTION()
	void OnMouseOverBegin(UPrimitiveComponent* TouchedComponent);
	void MoveUp();
	UFUNCTION()
	void OnMouseOverEnd(UPrimitiveComponent* TouchedComponent);
	void MoveDown();

	UAudioComponent* AudioComponent;
	UPROPERTY(EditAnywhere)
	USoundBase* PickUpSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
