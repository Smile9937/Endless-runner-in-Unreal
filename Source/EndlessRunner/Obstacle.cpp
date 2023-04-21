#include "Obstacle.h"
#include "Components/StaticMeshComponent.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Root = CreateDefaultSubobject<USceneComponent>("Root");

	Mesh->SetupAttachment(Root);
	SetRootComponent(Root);
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();
	Location += GetActorForwardVector() * ObstacleSpeed * DeltaTime;
	SetActorLocation(Location);
}