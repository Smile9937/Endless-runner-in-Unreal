#include "PlayerManager.h"
#include "EndlessRunnerCharacter.h"
#include "Components/SceneComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerViewport.h"

APlayerManager::APlayerManager()
{
	PrimaryActorTick.bCanEverTick = true;

	Player1SpawnPosition = CreateDefaultSubobject<USceneComponent>("Player 1 Spawn Position");
	Player2SpawnPosition = CreateDefaultSubobject<USceneComponent>("Player 2 Spawn Position");

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void APlayerManager::BeginPlay()
{
	Super::BeginPlay();
	
	Player1 = GetWorld()->SpawnActor<AEndlessRunnerCharacter>(PlayerSubclass, Player1SpawnPosition->GetComponentTransform());
	Player2 = GetWorld()->SpawnActor<AEndlessRunnerCharacter>(PlayerSubclass, Player2SpawnPosition->GetComponentTransform());

	GetLocalViewingPlayerController()->SetViewTargetWithBlend(Player1);
	SetupPlayer2Viewport(Player2);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APlayerManager::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveActionPlayer1, ETriggerEvent::Started, this, &APlayerManager::MovePlayer1);
		EnhancedInputComponent->BindAction(MoveActionPlayer2, ETriggerEvent::Started, this, &APlayerManager::MovePlayer2);
	}

}

void APlayerManager::MovePlayer1(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		FVector2D MovementVector = Value.Get<FVector2D>();

		Player1->Move(MovementVector.X);
	}
}

void APlayerManager::MovePlayer2(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		FVector2D MovementVector = Value.Get<FVector2D>();

		Player2->Move(MovementVector.X);
	}
}

void APlayerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}