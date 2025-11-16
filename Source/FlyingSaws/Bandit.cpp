// Fill out your copyright notice in the Description page of Project Settings.


#include "Bandit.h"
#include "Drum.h"
#include "Handle.h"
#include "ThrownObject.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABandit::ABandit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BanditBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bandit Body Mesh"));
	RootComponent = BanditBodyMesh;

	DrumsRef.SetNum(3);
}

// Called when the game starts or when spawned
void ABandit::BeginPlay()
{
	Super::BeginPlay();
	PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	HandleRef = GetWorld()->SpawnActor<AHandle>(HandleClass, GetActorLocation() + FVector(30, -110, -60), GetActorRotation() + FRotator(30, 0, 0));
	HandleRef->OnHandlePulled.AddUObject(PlayerRef, &APlayerCharacter::RemoveGold);

	for (int i = 0; i < 3; i++)
	{
		DrumsRef[i] = GetWorld()->SpawnActor<ADrum>(DrumClass, GetActorLocation() + FVector(0, 50 - (i * 50), 0), GetActorRotation() + FRotator(45 * i, 0, 0));
		FString DrumTag = FString::Printf(TEXT("Drum_%d"), i + 1);
		DrumsRef[i]->Tags.Add(*DrumTag);
		DrumsRef[i]->OnFinishedRotation.AddUObject(this, &ABandit::CheckDrumsResults);
		DrumsRef[i]->OnFinishedRotation.AddUObject(HandleRef, &AHandle::CanPull);
		HandleRef->OnHandlePulled.AddUObject(DrumsRef[i], &ADrum::HandlePulled);
	}
}

// Called every frame
void ABandit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ABandit::RandSpawnLocation(FVector Loc, int Range)
{
	float X = FMath::RandRange(Loc.X - Range, Loc.X + Range);
	float Y = FMath::RandRange(Loc.Y - Range, Loc.Y + Range);
	float Z = FMath::RandRange(Loc.Z - Range, Loc.Z + Range);
	return FVector(X, Y, Z);
}

FRotator ABandit::RandSpawnRotation(FRotator Rot, int Range)
{
	float Pitch = FMath::RandRange(Rot.Pitch - Range, Rot.Pitch + Range);
	float Yaw = FMath::RandRange(Rot.Yaw - Range, Rot.Yaw + Range);
	float Roll = FMath::RandRange(Rot.Roll - Range, Rot.Roll + Range);
	return FRotator(Pitch, Yaw, Roll);
}

void ABandit::CheckDrumsResults()
{
	TArray <EDrumResult> DrumResults;
	DrumResults.SetNum(3);
	for (int i = 0; i < 3; i++)
	{
		DrumResults[i] = DrumsRef[i]->DrumResult();
	}
	if ((DrumResults[0] == EDrumResult::Paluch || DrumResults[1] == EDrumResult::Paluch || DrumResults[2] == EDrumResult::Paluch) &&
		(DrumResults[0] == EDrumResult::Paluch || DrumResults[0] == EDrumResult::Korona) &&
		(DrumResults[1] == EDrumResult::Paluch || DrumResults[1] == EDrumResult::Korona) &&
		(DrumResults[2] == EDrumResult::Paluch || DrumResults[2] == EDrumResult::Korona))
	{
		PlayerRef->CutFinger();
		MaxThrowCount = 3;
		ObjectToThrow = SawToSpawn;
		GetWorldTimerManager().SetTimer(ThrowTimerHandle, this, &ABandit::Throw, 0.1f, true);
	}
	else if ((DrumResults[0] == EDrumResult::Ogor || DrumResults[1] == EDrumResult::Ogor || DrumResults[2] == EDrumResult::Ogor) &&
		(DrumResults[0] == EDrumResult::Ogor || DrumResults[0] == EDrumResult::Korona) &&
		(DrumResults[1] == EDrumResult::Ogor || DrumResults[1] == EDrumResult::Korona) &&
		(DrumResults[2] == EDrumResult::Ogor || DrumResults[2] == EDrumResult::Korona))
	{
		PlayerRef->AddGold(OgorPrize);
		MaxThrowCount = OgorPrize;
		ObjectToThrow = GoldToSpawn;
		GetWorldTimerManager().SetTimer(ThrowTimerHandle, this, &ABandit::Throw, 0.1f, true);
	}
	else if ((DrumResults[0] == EDrumResult::Wisnie || DrumResults[1] == EDrumResult::Wisnie || DrumResults[2] == EDrumResult::Wisnie) &&
		(DrumResults[0] == EDrumResult::Wisnie || DrumResults[0] == EDrumResult::Korona) &&
		(DrumResults[1] == EDrumResult::Wisnie || DrumResults[1] == EDrumResult::Korona) &&
		(DrumResults[2] == EDrumResult::Wisnie || DrumResults[2] == EDrumResult::Korona))
	{
		PlayerRef->AddGold(WisniePrize);
		MaxThrowCount = WisniePrize;
		ObjectToThrow = GoldToSpawn;
		GetWorldTimerManager().SetTimer(ThrowTimerHandle, this, &ABandit::Throw, 0.1f, true);
	}
	else if (DrumResults[0] == EDrumResult::Korona && DrumResults[1] == EDrumResult::Korona && DrumResults[2] == EDrumResult::Korona)
	{
		PlayerRef->AddGold(KoronaPrize);
		MaxThrowCount = KoronaPrize;
		ObjectToThrow = GoldToSpawn;
		GetWorldTimerManager().SetTimer(ThrowTimerHandle, this, &ABandit::Throw, 0.1f, true);
	}
	else
	{
	}
}

void ABandit::Throw()
{
	AThrownObject* Object = GetWorld()->SpawnActor<AThrownObject>(ObjectToThrow, RandSpawnLocation(GoldSpawnLocation, SpawnLocationRadius), RandSpawnRotation(GoldSpawnRotation, SpawnRotationRadius));
	if (ObjectToThrow == SawToSpawn)
	{
		Object->ThrowObjectWithRotation(true);
	}
	else
	{
		Object->ThrowObjectWithRotation(false);
	}
	ThrowCount++;
	if (ThrowCount >= MaxThrowCount)
	{
		GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		ThrowCount = 0;
		MaxThrowCount = 0;
	}
}