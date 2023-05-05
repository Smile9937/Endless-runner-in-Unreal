// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Components/TimelineComponent.h"
#include "EndlessRunnerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UInputComponent;
class ALaneManager;
class UGameData;

UCLASS(config=Game)
class AEndlessRunnerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true")) 
	TObjectPtr<USpringArmComponent> CameraBoom;


	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> DodgeAction;

	FVector StartPosition;
	FVector ClampedPosition;

	TArray<FVector> MovePoints;
	int8 MovePointIndex;
	FVector CurrentPosition;
	FVector NextPosition;

	bool WaitingToMove;

public:
	AEndlessRunnerCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UGameData> GameData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCurveFloat> FloatCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	float YMovementLength;

	UPROPERTY()
	TObjectPtr<UTimelineComponent> Timeline;

	FOnTimelineFloat InterpFunction{};
	FOnTimelineEvent TimelineFunction{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<UCameraComponent> FollowCamera;

	UFUNCTION()
	void TimelineFloatReturn(float value);

	UFUNCTION()
	void TimelineFinished();

	void Move(const int8 Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int CurrentHealth;

	UFUNCTION()
	void ReduceHealth();

protected:


	virtual void Tick(float DeltaTime) override;
			

protected:
	virtual void BeginPlay();

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

