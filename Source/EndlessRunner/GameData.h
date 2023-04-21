#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameData.generated.h"

UCLASS()
class ENDLESSRUNNER_API UGameData : public UDataAsset
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DespawnXPosition;
};