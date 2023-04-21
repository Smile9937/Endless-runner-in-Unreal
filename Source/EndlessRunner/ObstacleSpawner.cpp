#include "ObstacleSpawner.h"
#include "GameData.h"
#include "Components/ArrowComponent.h"

AObstacleSpawner::AObstacleSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnIndex = 0;

	ForwardVector = CreateDefaultSubobject<UArrowComponent>("Forward Vector");
}

void AObstacleSpawner::OnSpawn()
{
	TSubclassOf<AActor> ActorToSpawn = ActorsToSpawn[SpawnIndex];

	TObjectPtr<AActor> SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, GetActorTransform());

	SpawnedActors.Add(SpawnedActor);

	if (SpawnIndex >= ActorsToSpawn.Num() - 1) { SpawnIndex = 0; }
	else { SpawnIndex++; }
}

void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AObstacleSpawner::OnSpawn, SpawnTime, true);
	
}

void AObstacleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}