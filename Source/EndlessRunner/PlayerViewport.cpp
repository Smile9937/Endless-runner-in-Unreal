#include "PlayerViewport.h"

APlayerViewport::APlayerViewport()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player1;
}

void APlayerViewport::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerViewport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerViewport::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

