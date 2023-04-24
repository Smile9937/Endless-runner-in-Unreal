#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawner.generated.h"

class UGameData;
class UArrowComponent;

UCLASS()
class ENDLESSRUNNER_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacleSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float SpawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	TArray<TSubclassOf<AActor>> ActorsToSpawn;

	int32 SpawnIndex;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> SpawnedActors;

	UFUNCTION()
	void OnSpawn();

	FTimerHandle SpawnTimerHandle;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UArrowComponent> ForwardVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UGameData> GameData;

	TArray<FVector> SpawnPositions;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
