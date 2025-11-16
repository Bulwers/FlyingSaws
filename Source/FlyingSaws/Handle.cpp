// Fill out your copyright notice in the Description page of Project Settings.


#include "Handle.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHandle::AHandle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HandleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandleMesh"));
	RootComponent = HandleMesh;
	bIsReturning = false;
	bCanPull = false;
}

// Called when the game starts or when spawned
void AHandle::BeginPlay()
{
	Super::BeginPlay();
	
	OnClicked.AddDynamic(this, &AHandle::HandlePull);

	StartRot = HandleMesh->GetComponentRotation();
}

// Called every frame
void AHandle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHandle::MoveHandle()
{
	if (!bIsReturning)
	{
		HandleMesh->SetWorldRotation(FMath::RInterpConstantTo(HandleMesh->GetComponentRotation(), EndRot, GetWorld()->GetDeltaSeconds(), HandleMoveSpeed));
		if (HandleMesh->GetComponentRotation().Equals(EndRot, 0.2))
		{
			bIsReturning = true;
			OnHandlePulled.Broadcast();
		}
	}
	if (bIsReturning)
	{
		HandleMesh->SetWorldRotation(FMath::RInterpConstantTo(HandleMesh->GetComponentRotation(), StartRot, GetWorld()->GetDeltaSeconds(), HandleMoveSpeed));
		if (HandleMesh->GetComponentRotation().Equals(StartRot, 0.2))
		{
			GetWorldTimerManager().ClearTimer(HandleMoveTimer);
			bIsReturning = false;
		}
	}
}


void AHandle::HandlePull(AActor* ActorClicked, FKey InKey)
{
	if (!bCanPull)
	{
		GetWorldTimerManager().SetTimer(HandleMoveTimer, this, &AHandle::MoveHandle, HandleUppdateTime, true);
		if (HandlePullSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HandlePullSound, GetActorLocation());
		}
	}
	bCanPull = true;
}

void AHandle::CanPull()
{
	bCanPull = false;
}