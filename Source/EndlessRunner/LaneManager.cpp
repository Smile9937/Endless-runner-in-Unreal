#include "LaneManager.h"

ALaneManager::ALaneManager()
{
	PrimaryActorTick.bCanEverTick = true;

	Lane1 = CreateDefaultSubobject<USceneComponent>("Lane 1");
	Lane2 = CreateDefaultSubobject<USceneComponent>("Lane 2");
	Lane3 = CreateDefaultSubobject<USceneComponent>("Lane 3");
	Root = CreateDefaultSubobject<USceneComponent>("Root");

	SetRootComponent(Root);
	Lane1->SetupAttachment(Root);
	Lane2->SetupAttachment(Root);
	Lane3->SetupAttachment(Root);
}

void ALaneManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALaneManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

