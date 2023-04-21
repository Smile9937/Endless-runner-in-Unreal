#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DespawnZone.generated.h"

class UBoxComponent;

UCLASS()
class ENDLESSRUNNER_API ADespawnZone : public AActor
{
	GENERATED_BODY()
	
public:	
	ADespawnZone();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> Collider;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};