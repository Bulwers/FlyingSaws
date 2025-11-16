// Fill out your copyright notice in the Description page of Project Settings.


#include "Rules.h"
#include "Components/AudioComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ARules::ARules()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RulesMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rules Mesh"));
	RootComponent = RulesMesh;

	RulesMesh->SetGenerateOverlapEvents(true);
	RulesMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RulesMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	RulesMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	RulesMesh->OnBeginCursorOver.AddDynamic(this, &ARules::OnMouseOverBegin);
	RulesMesh->OnEndCursorOver.AddDynamic(this, &ARules::OnMouseOverEnd);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Rules Audio"));
}

// Called when the game starts or when spawned
void ARules::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	StartRotation = GetActorRotation();
	AudioComponent->SetSound(PickUpSound);
}

// Called every frame
void ARules::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARules::MoveUp()
{
	RulesMesh->SetWorldLocation(FMath::VInterpConstantTo(RulesMesh->GetComponentLocation(), StartLocation + AddLocation, GetWorld()->GetDeltaSeconds(), MoveSpeed));
	RulesMesh->SetWorldRotation(FMath::RInterpConstantTo(RulesMesh->GetComponentRotation(), StartRotation + AddRotation, GetWorld()->GetDeltaSeconds(), MoveSpeed));
	if (GetActorLocation().Equals(StartLocation + AddLocation, 0.2) && GetActorRotation().Equals(StartRotation + AddRotation, 0.2))
	{
		GetWorldTimerManager().ClearTimer(MoveTimerHandle);
	}
}

void ARules::MoveDown()
{
	RulesMesh->SetWorldLocation(FMath::VInterpConstantTo(RulesMesh->GetComponentLocation(), StartLocation, GetWorld()->GetDeltaSeconds(), MoveSpeed));
	RulesMesh->SetWorldRotation(FMath::RInterpConstantTo(RulesMesh->GetComponentRotation(), StartRotation, GetWorld()->GetDeltaSeconds(), MoveSpeed));
	if (GetActorLocation().Equals(StartLocation, 0.2) && GetActorRotation().Equals(StartRotation, 0.2))
	{
		GetWorldTimerManager().ClearTimer(MoveTimerHandle);
	}
}

void ARules::OnMouseOverBegin(UPrimitiveComponent* TouchedComponent)
{
	GetWorldTimerManager().SetTimer(MoveTimerHandle, this, &ARules::MoveUp, 0.05f, true);
	float RandomPitch = FMath::FRandRange(1.f, 1.05f);
	AudioComponent->SetPitchMultiplier(RandomPitch);
	AudioComponent->Play();
}

void ARules::OnMouseOverEnd(UPrimitiveComponent* TouchedComponent)
{
	GetWorldTimerManager().SetTimer(MoveTimerHandle, this, &ARules::MoveDown, 0.05f, true);
	float RandomPitch = FMath::FRandRange(0.95f, 1.f);
	AudioComponent->SetPitchMultiplier(RandomPitch);
	AudioComponent->Play();
}