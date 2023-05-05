#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "CoinPickup.generated.h"

class USphereComponent;

UCLASS()
class ENDLESSRUNNER_API ACoinPickup : public AActor
{
	GENERATED_BODY()

public:
	ACoinPickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpinSpeed;

	UPROPERTY()
	TObjectPtr<UTimelineComponent> Timeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCurveFloat> FloatCurve;

	FOnTimelineFloat TimelineFloat{};
	FOnTimelineEvent TimelineFunction{};

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> AnimationTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> Collider;

	UFUNCTION()
	void TimelineFloatReturn(float val);

	UFUNCTION()
	void TimelineFinished();

	FVector StartPosition;
	FVector TargetPosition;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
