// Fill out your copyright notice in the Description page of Project Settings.


#include "PersistancePlayerController.h"

APersistancePlayerController::APersistancePlayerController()
{
	
}

void APersistancePlayerController::BeginPlay()
{
	if (!HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("RUNNING ON CLIENT"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("RUNNING ON SERVER"));
	}
}
