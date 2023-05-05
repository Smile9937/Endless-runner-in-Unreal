#include "Obstacle.h"
#include "Components/StaticMeshComponent.h"
#include "EndlessRunnerCharacter.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Root = CreateDefaultSubobject<USceneComponent>("Root");

	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnOverlapBegin);

	Mesh->SetupAttachment(Root);
	SetRootComponent(Root);
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AObstacle::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TObjectPtr<AEndlessRunnerCharacter> Player = Cast<AEndlessRunnerCharacter>(OtherActor);

	if (Player)
	{
		Player->ReduceHealth();
	}
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();
	Location += GetActorForwardVector() * MovementSpeed * DeltaTime;
	SetActorLocation(Location);
}