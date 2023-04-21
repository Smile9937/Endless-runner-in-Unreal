// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundSpawner.generated.h"

class UGameData;
class UArrowComponent;

UCLASS()
class ENDLESSRUNNER_API AGroundSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AGroundSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> GroundTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfTiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DespawnXOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UGameData> GameData;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> SpawnedGroundTiles;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UArrowComponent> ForwardVector;

	UFUNCTION()
	void SpawnTile();

	FTimerHandle SpawnTimerHandle;

	FVector SpawnPosition;

	FVector DespawnPosition;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
