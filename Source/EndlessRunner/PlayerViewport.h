#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerViewport.generated.h"

UCLASS()
class ENDLESSRUNNER_API APlayerViewport : public APawn
{
	GENERATED_BODY()

public:
	APlayerViewport();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
