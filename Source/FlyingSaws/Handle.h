// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Handle.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHandlePulled);

UCLASS()
class FLYINGSAWS_API AHandle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandle();

	FOnHandlePulled OnHandlePulled;
	void CanPull();

private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* HandleMesh;

	FTimerHandle HandleMoveTimer;
	FRotator StartRot;
	UPROPERTY(EditDefaultsOnly)
	FRotator EndRot;
	UPROPERTY(EditAnywhere, Category = "Handle")
	float HandleMoveSpeed;
	UPROPERTY(EditAnywhere, Category = "Handle")
	float HandleUppdateTime;
	void MoveHandle();
	bool bIsReturning;
	bool bCanPull;

	UFUNCTION()
	void HandlePull(AActor* ActorClicked, FKey InKey);

	UPROPERTY(EditAnywhere)
	USoundBase* HandlePullSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
