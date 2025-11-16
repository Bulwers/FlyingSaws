// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bandit.generated.h"

class ADrum;
class AHandle;
class APlayerCharacter;
class AThrownObject;

UCLASS()
class FLYINGSAWS_API ABandit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABandit();

	UFUNCTION(BlueprintCallable)
	void Throw();

private:

	APlayerCharacter* PlayerRef;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BanditBodyMesh;

	UPROPERTY(VisibleAnywhere, Category = "Parts")
	AHandle* HandleRef;
	UPROPERTY(EditDefaultsOnly, Category = "Parts")
	TSubclassOf<AHandle> HandleClass;
	UPROPERTY(VisibleAnywhere, Category = "Parts")
	TArray<ADrum*> DrumsRef;
	UPROPERTY(EditDefaultsOnly, Category = "Parts")
	TSubclassOf<ADrum> DrumClass;

	void CheckDrumsResults();
	UPROPERTY(EditDefaultsOnly, Category = "Prizes")
	int OgorPrize;
	UPROPERTY(EditDefaultsOnly, Category = "Prizes")
	int WisniePrize;
	UPROPERTY(EditDefaultsOnly, Category = "Prizes")
	int KoronaPrize;


	UPROPERTY(EditDefaultsOnly, Category = "Items")
	TSubclassOf<AThrownObject> GoldToSpawn;
	UPROPERTY(EditDefaultsOnly, Category = "Items")
	TSubclassOf<AThrownObject> SawToSpawn;
	TSubclassOf<AThrownObject> ObjectToThrow;
	

	FTimerHandle ThrowTimerHandle;
	int ThrowCount = 0;
	int MaxThrowCount = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Gold")
	FVector GoldSpawnLocation;
	UPROPERTY(EditDefaultsOnly, Category = "Gold")
	FRotator GoldSpawnRotation;
	UPROPERTY(EditDefaultsOnly, Category = "Gold")
	int SpawnLocationRadius;
	UPROPERTY(EditDefaultsOnly, Category = "Gold")
	int SpawnRotationRadius;
	FVector RandSpawnLocation(FVector Loc, int Range);
	FRotator RandSpawnRotation(FRotator Rot, int Range);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
