#include "ObstacleSpawner.h"
#include "GameData.h"
#include "Components/ArrowComponent.h"
#include "Obstacle.h"
#include "CoinPickup.h"

AObstacleSpawner::AObstacleSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnIndex = 0;

	ForwardVector = CreateDefaultSubobject<UArrowComponent>("Forward Vector");

	SpawnSpeedCurve = CreateDefaultSubobject<UCurveFloat>("Spawn Speed Curve");

	ObstacleSpeedCurve = CreateDefaultSubobject<UCurveFloat>("Obstacle Speed Curve");

	SpawnPositions.Init(FVector(0, 0, 0), 3);
}

void AObstacleSpawner::OnSpawn()
{
	TSubclassOf<AActor> ActorToSpawn = ActorsToSpawn[SpawnIndex];

	int8 RandomIndex = FMath::RandRange(0, SpawnPositions.Num() - 1);
	FVector SpawnPosition = SpawnPositions[RandomIndex];

	TObjectPtr<AActor> SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnPosition, GetActorRotation());

	TObjectPtr<AObstacle> Obstacle = Cast<AObstacle>(SpawnedActor);
	if(Obstacle)
	{
		Obstacle->MovementSpeed = ObstacleSpeedCurve->GetFloatValue(TimeSinceGameStart);
	}

	TObjectPtr<ACoinPickup> Coin = Cast<ACoinPickup>(SpawnedActor);
	if (Coin)
	{
		Coin->MovementSpeed = ObstacleSpeedCurve->GetFloatValue(TimeSinceGameStart);
	}

	SpawnedActors.Add(SpawnedActor);

	if (SpawnIndex >= ActorsToSpawn.Num() - 1) { SpawnIndex = 0; }
	else { SpawnIndex++; }

	if (SpawnSpeedCurve == nullptr) return;
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AObstacleSpawner::OnSpawn, SpawnSpeedCurve->GetFloatValue(TimeSinceGameStart), false);
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

	if (SpawnSpeedCurve == nullptr) return;
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AObstacleSpawner::OnSpawn, SpawnSpeedCurve->GetFloatValue(0), false);
	
}

void AObstacleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeSinceGameStart += DeltaTime;
}