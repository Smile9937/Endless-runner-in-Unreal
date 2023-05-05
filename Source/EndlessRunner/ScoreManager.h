#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreManager.generated.h"

USTRUCT(BlueprintType)
struct FScoreboardStruct
{
	GENERATED_BODY()

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	int Score;

	static FScoreboardStruct BuildStruct(FString PlayerName, int32 PlayerScore)
	{
		FScoreboardStruct ScoreboardStruct;
		ScoreboardStruct.PlayerName = PlayerName;
		ScoreboardStruct.Score = PlayerScore;
		return ScoreboardStruct;
	};
};

UCLASS()
class ENDLESSRUNNER_API AScoreManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AScoreManager();

	TArray<FScoreboardStruct> GenerateStructsFromJson(FString Path);

	void GenerateStructsFromJson(TArray<FScoreboardStruct>& ScoreboardStructs, TSharedPtr<FJsonObject> JsonObject);

	FString JsonFullPath(FString Path);

	FString FStructToJsonString(FScoreboardStruct ScoreboardStruct);

	void AddToAndSortScoreboard(FScoreboardStruct ScoreboardStruct);
protected:
	virtual void BeginPlay() override;


public:	
	virtual void Tick(float DeltaTime) override;

};
