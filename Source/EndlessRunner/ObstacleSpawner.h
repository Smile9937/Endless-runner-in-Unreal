#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawner.generated.h"

class UGameData;
class UArrowComponent;
class UCurveFloat;

UCLASS()
class ENDLESSRUNNER_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacleSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AActor>> ActorsToSpawn;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> SpawnedActors;

	int32 SpawnIndex;

	UFUNCTION()
	void OnSpawn();

	FTimerHandle SpawnTimerHandle;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UArrowComponent> ForwardVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UGameData> GameData;

	UPROPERTY()
	TArray<FVector> SpawnPositions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCurveFloat> SpawnSpeedCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCurveFloat> ObstacleSpeedCurve;

	float TimeSinceGameStart;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
