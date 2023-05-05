#include "CoinPickup.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
#include "EndlessRunnerCharacter.h"

ACoinPickup::ACoinPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	Timeline = CreateDefaultSubobject<UTimelineComponent>("Timeline");
	FloatCurve = CreateDefaultSubobject<UCurveFloat>("Float Curve");
	AnimationTarget = CreateDefaultSubobject<USceneComponent>("Animation Target");

	Collider = CreateDefaultSubobject<USphereComponent>("Collider");
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACoinPickup::OnOverlapBegin);

	SetRootComponent(Collider);
	AnimationTarget->SetupAttachment(Collider);

	TimelineFunction.BindUFunction(this, FName{ TEXT("TimelineFinished") });
	TimelineFloat.BindUFunction(this, FName{ TEXT("TimelineFloatReturn") });
}

void ACoinPickup::BeginPlay()
{
	Super::BeginPlay();

	Timeline->AddInterpFloat(FloatCurve, TimelineFloat, FName{ TEXT("Interp Float") });
	Timeline->SetTimelineFinishedFunc(TimelineFunction);
	Timeline->SetLooping(true);

	StartPosition = AnimationTarget->GetRelativeLocation();
	TargetPosition = StartPosition;
	TargetPosition.Z += MovementHeight;

	Timeline->Play();
}

void ACoinPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();
	Location += GetActorForwardVector() * MovementSpeed * DeltaTime;
	SetActorLocation(Location);
}

void ACoinPickup::TimelineFinished()
{
	TargetPosition = AnimationTarget->GetRelativeLocation();
}

void ACoinPickup::TimelineFloatReturn(float val)
{
	FVector LerpedPosition = FMath::Lerp(StartPosition, TargetPosition, val);
	AnimationTarget->SetRelativeLocation(LerpedPosition);

	FRotator Rotation = AnimationTarget->GetRelativeRotation();
	Rotation.Yaw += SpinSpeed;
	AnimationTarget->SetRelativeRotation(Rotation);
}

void ACoinPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TObjectPtr<AEndlessRunnerCharacter> Character = Cast<AEndlessRunnerCharacter>(OtherActor);

	if (Character)
	{
		Destroy();
	}
}