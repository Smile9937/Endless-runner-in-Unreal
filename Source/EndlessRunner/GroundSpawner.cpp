#include "GroundSpawner.h"
#include "GameData.h"
#include "Components/ArrowComponent.h"


AGroundSpawner::AGroundSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	ForwardVector = CreateDefaultSubobject<UArrowComponent>("Forward Vector");
}

void AGroundSpawner::SpawnTile()
{
	if (!SpawnedGroundTiles.IsEmpty()) {
		SpawnPosition = SpawnedGroundTiles.Last()->GetActorLocation();

		FVector boundsExtent;
		FVector origin;
		SpawnedGroundTiles.Last()->GetActorBounds(true, origin, boundsExtent);

		SpawnPosition.X = origin.X + boundsExtent.X * 2;
	}
	else
	{
		SpawnPosition = GetActorLocation();
	}

	TObjectPtr<AActor> groundTile = GetWorld()->SpawnActor<AActor>(GroundTile, SpawnPosition, GetActorRotation());

	SpawnedGroundTiles.Add(groundTile);
}

void AGroundSpawner::BeginPlay()
{
	Super::BeginPlay();

	DespawnPosition = GetActorLocation();
	DespawnPosition.X -= DespawnXOffset;

	for (int32 i = 0; i < NumberOfTiles; i++)
	{
		SpawnTile();
	}

	//GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AGroundSpawner::OnSpawn, SpawnTime, true);
}

void AGroundSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for(int i = 0; i < SpawnedGroundTiles.Num(); i++)
	{
		TObjectPtr<AActor> currentTile = SpawnedGroundTiles[i];
		FVector currentLocation = currentTile->GetActorLocation();

		currentLocation += currentTile->GetActorForwardVector() * MoveSpeed * DeltaTime;
		currentTile->SetActorLocation(currentLocation);

		if (currentTile == SpawnedGroundTiles[0])
		{
			if (GameData == nullptr) continue;

			if (currentLocation.X <= GameData->DespawnXPosition)
			{
				SpawnedGroundTiles.Remove(currentTile);
				currentTile->Destroy();
				SpawnTile();
			}
		}
	}
}