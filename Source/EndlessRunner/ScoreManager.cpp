#include "ScoreManager.h"
#include <Runtime/JsonUtilities/Public/JsonObjectConverter.h>

AScoreManager::AScoreManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

TArray<FScoreboardStruct> AScoreManager::GenerateStructsFromJson(FString Path)
{
	FString JsonStr;
	FFileHelper::LoadFileToString(JsonStr, *Path);

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	TArray<FScoreboardStruct> ScoreboardStructs;

	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, JsonStr);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Deserialize"));
		}

		GenerateStructsFromJson(ScoreboardStructs, JsonObject);
	}
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Not Deserialize"));
		}
	}

	return ScoreboardStructs;
}

void AScoreManager::GenerateStructsFromJson(TArray<FScoreboardStruct>& ScoreboardStructs, TSharedPtr<FJsonObject> JsonObject)
{
	TArray<TSharedPtr<FJsonValue>> objArray = JsonObject->GetArrayField(TEXT("ScoreboardStructs"));

	for (int32 i = 0; i < objArray.Num(); i++)
	{
		TSharedPtr<FJsonValue> value = objArray[i];
		TSharedPtr<FJsonObject> json = value->AsObject();

		FString AwesomeFloat = json->GetStringField(TEXT("PlayerName"));
		int32 AwesomeInteger = json->GetNumberField(TEXT("PlayerScore"));

		FScoreboardStruct AwesomeStruct = FScoreboardStruct::BuildStruct(AwesomeFloat, AwesomeInteger);

		ScoreboardStructs.Push(AwesomeStruct);
	}
}

FString AScoreManager::JsonFullPath(FString Path)
{
	FString FullPath = FPaths::ProjectContentDir();
	FullPath += Path;
	//FString JsonStr;

	//FFileHelper::LoadFileToString(JsonStr, *FullPath);

	return FullPath;
}

void AScoreManager::BeginPlay()
{
	Super::BeginPlay();
	

	FString PlayerName = "John";

	int Score = 999;

	FScoreboardStruct ScoreboardStruct = FScoreboardStruct::BuildStruct(PlayerName, Score);

	AddToAndSortScoreboard(ScoreboardStruct);

	//TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(ScoreboardStruct);


	//FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<>::Create(&JsonString, 0));





	//GenerateStructsFromJson(Path);
	
}

FString AScoreManager::FStructToJsonString(FScoreboardStruct ScoreboardStruct)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	JsonObject->SetStringField("PlayerName", ScoreboardStruct.PlayerName);
	JsonObject->SetNumberField("Score", ScoreboardStruct.Score);

	FString OutputString;
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	return OutputString;
	//UE_LOG(LogTemp, Warning, TEXT("resulting jsonString -> %s"), *OutputString);
}

void AScoreManager::AddToAndSortScoreboard(FScoreboardStruct ScoreboardStruct)
{
	FString Path = JsonFullPath("Scoreboard.json");
	TArray<FScoreboardStruct> ScoreboardEntries = GenerateStructsFromJson(Path);


	if (ScoreboardEntries.Num() > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("1")));
		/*for (int i = 0; ScoreboardEntries.Num(); i++)
		{
			if (ScoreboardStruct.Score < ScoreboardEntries[i].Score)
			{
				ScoreboardEntries.Insert(ScoreboardStruct, i - 1);
				break;
			}
		}
		ScoreboardEntries.Add(ScoreboardStruct);*/
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("2")));
		ScoreboardEntries.Add(ScoreboardStruct);
	}

	FString JsonString;

		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("%f"), ScoreboardEntries.Num()));
	/*for (int i = 0; ScoreboardEntries.Num(); i++)
	{
		JsonString.Append(FStructToJsonString(ScoreboardEntries[i]));
		JsonString.Append(",");
	}*/

	FFileHelper::SaveStringToFile(JsonString, *Path);
}

void AScoreManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

