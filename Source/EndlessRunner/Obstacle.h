#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

class UStaticMeshComponent;

UCLASS()
class ENDLESSRUNNER_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ObstacleSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};