#include "DespawnZone.h"
#include "Components/BoxComponent.h"

ADespawnZone::ADespawnZone()
{
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	Collider->SetCollisionResponseToAllChannels(ECR_Overlap);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider->SetGenerateOverlapEvents(true);

	RootComponent = Collider;

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ADespawnZone::OnOverlapBegin);
}

void ADespawnZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->Destroy();
}

void ADespawnZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADespawnZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}