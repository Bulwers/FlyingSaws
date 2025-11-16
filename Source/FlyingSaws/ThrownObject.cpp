// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrownObject.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AThrownObject::AThrownObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThrownObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Thrown Object Mesh"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Thrown Object Audio"));
	RootComponent = ThrownObjectMesh;
}

// Called when the game starts or when spawned
void AThrownObject::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AThrownObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AThrownObject::ThrowObjectWithRotation(bool bCanRotate)
{
	if (bCanRotate)
	{
		GetWorldTimerManager().SetTimer(RotateObjectTimer, this, &AThrownObject::RotateObject, 0.005f, true);
	}
	ThrownObjectMesh->AddImpulse(GetActorForwardVector() * ThrowStrenght, NAME_None, true);
	AudioComponent->SetSound(ThrownSound);
	float RandomPitch = FMath::FRandRange(1.f, 1.05f);
	AudioComponent->SetPitchMultiplier(RandomPitch);
	AudioComponent->Play();

	SetLifeSpan(3.f);
}

void AThrownObject::RotateObject()
{
	ThrownObjectMesh->AddLocalRotation(FRotator(0.f, 15.f, 0.f) * -1);
}