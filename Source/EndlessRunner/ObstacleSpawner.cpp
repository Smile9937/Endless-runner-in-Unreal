#include "ObstacleSpawner.h"
#include "GameData.h"
#include "Components/ArrowComponent.h"

AObstacleSpawner::AObstacleSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnIndex = 0;

	ForwardVector = CreateDefaultSubobject<UArrowComponent>("Forward Vector");

	SpawnPositions.Init(FVector(0, 0, 0), 3);
}

void AObstacleSpawner::OnSpawn()
{
	TSubclassOf<AActor> ActorToSpawn = ActorsToSpawn[SpawnIndex];

	int8 RandomIndex = FMath::RandRange(0, SpawnPositions.Num() - 1);
	FVector SpawnPosition = SpawnPositions[RandomIndex];

	TObjectPtr<AActor> SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnPosition, GetActorRotation());

	SpawnedActors.Add(SpawnedActor);

	if (SpawnIndex >= ActorsToSpawn.Num() - 1) { SpawnIndex = 0; }
	else { SpawnIndex++; }
}

void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();

	FVector StartPosition = GetActorLocation();

	SpawnPositions[1] = StartPosition;

	SpawnPositions[0] = StartPosition;
	SpawnPositions[0].Y -= GameData->DistanceBetweenLanes;

	SpawnPositions[2] = StartPosition;
	SpawnPositions[2].Y += GameData->DistanceBetweenLanes;

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AObstacleSpawner::OnSpawn, SpawnTime, true);
	
}

void AObstacleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}