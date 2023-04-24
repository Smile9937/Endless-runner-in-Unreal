#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaneManager.generated.h"

UCLASS()
class ENDLESSRUNNER_API ALaneManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ALaneManager();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> Lane1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> Lane2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> Lane3;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
	TArray<FVector> LanePositions;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
