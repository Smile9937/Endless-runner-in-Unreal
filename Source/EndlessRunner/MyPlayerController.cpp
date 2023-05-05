// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//UPlayer* FirstPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	UPlayer* FirstPlayer = GEngine->GetFirstGamePlayer(GetWorld());

	/*Player = FirstPlayer;
	SetAsLocalPlayerController();
	InitInputSystem();*/
	//SetPlayer(FirstPlayer);
	//if(FirstPlayer->GetPlayerController(GetWorld()) != this)
	//PlayerInput = FirstPlayer->GetPlayerController(GetWorld())->PlayerInput;
}