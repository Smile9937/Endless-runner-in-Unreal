#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerManager.generated.h"

class AEndlessRunnerCharacter;
class USceneComponent;
class UInputMappingContext;
class UInputAction;
class APlayerViewport;

UCLASS()
class ENDLESSRUNNER_API APlayerManager : public APawn
{
	GENERATED_BODY()

public:
	APlayerManager();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveActionPlayer1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveActionPlayer2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> PlayerSubclass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<AEndlessRunnerCharacter> Player1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<AEndlessRunnerCharacter> Player2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> Player1SpawnPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> Player2SpawnPosition;

	UFUNCTION(BlueprintImplementableEvent)
	void SetupPlayer2Viewport(AEndlessRunnerCharacter* Character);

protected:
	virtual void BeginPlay() override;

	void MovePlayer1(const FInputActionValue& Value);
	void MovePlayer2(const FInputActionValue& Value);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
