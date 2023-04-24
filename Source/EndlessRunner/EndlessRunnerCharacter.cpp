// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "LaneManager.h"
#include "GameData.h"


//////////////////////////////////////////////////////////////////////////
// AEndlessRunnerCharacter

AEndlessRunnerCharacter::AEndlessRunnerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	FloatCurve = CreateDefaultSubobject<UCurveFloat>("Float Curve");
	Timeline = CreateDefaultSubobject<UTimelineComponent>("Timeline");

	InterpFunction.BindUFunction(this, FName{ TEXT("TimelineFloatReturn") });
	TimelineFunction.BindUFunction(this, FName{ TEXT("TimelineFinished") });

	MovePointIndex = 1;

	MovePoints.Init(FVector(0, 0, 0), 3);
}

void AEndlessRunnerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	StartPosition = GetActorLocation();

	CurrentPosition = StartPosition;

	MovePoints[1] = StartPosition;

	MovePoints[0] = StartPosition;
	MovePoints[0].Y -= GameData->DistanceBetweenLanes;

	MovePoints[2] = StartPosition;
	MovePoints[2].Y += GameData->DistanceBetweenLanes;

	Timeline->AddInterpFloat(FloatCurve, InterpFunction, FName{ TEXT("Curve Foat") });
	Timeline->SetTimelineFinishedFunc(TimelineFunction);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AEndlessRunnerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AEndlessRunnerCharacter::Move);
	}

}

void AEndlessRunnerCharacter::TimelineFloatReturn(float value)
{
	FVector LerpedPosition = FMath::Lerp(CurrentPosition, NextPosition, value);
	SetActorLocation(LerpedPosition);
}

void AEndlessRunnerCharacter::TimelineFinished()
{
	WaitingToMove = false;
}

void AEndlessRunnerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (!WaitingToMove)
		{

			if(MovementVector.X > 0)
			{
				if(MovePoints.Num() - 1 > MovePointIndex)
				{
					WaitingToMove = true;
					MovePointIndex++;
					NextPosition = MovePoints[MovePointIndex];
					Timeline->PlayFromStart();
				}
			}
			else
			{
				if (MovePointIndex - 1 >= 0)
				{
					WaitingToMove = true;
					MovePointIndex--;
					NextPosition = MovePoints[MovePointIndex];
					Timeline->PlayFromStart();
				}
			}
		}
	}
}

void AEndlessRunnerCharacter::Tick(float DeltaTime)
{
}