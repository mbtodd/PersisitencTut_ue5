// Copyright Epic Games, Inc. All Rights Reserved.

#include "PersistenceTut_ue5GameMode.h"

#include "JsonObjectConverter.h"
#include "PersistenceTut_ue5Character.h"
#include "UObject/ConstructorHelpers.h"

APersistenceTut_ue5GameMode::APersistenceTut_ue5GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	Http = &FHttpModule::Get();
}

void APersistenceTut_ue5GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(LogTemp, Display, TEXT("POST LOGIN RUNNING"));


	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	
	Request ->OnProcessRequestComplete().BindUObject(this, &APersistenceTut_ue5GameMode::OnProcessRequestComplete);
	Request ->SetURL("http://localhost:8080/api/PlayerData");
	Request ->SetVerb("POST");
	Request ->SetHeader(TEXT("Content-Type"), "application/json");

	FString JsonString;
	FPlayerData PlayerData;
	PlayerData.Xcoord = 1111.0f;
	PlayerData.Ycoord = 2222.0f;
	PlayerData.Zcoord = 3333.0f;
	
	FJsonObjectConverter::UStructToJsonObjectString(PlayerData, JsonString); 
	Request ->SetContentAsString(JsonString);
	UE_LOG(LogTemp, Warning, TEXT("Json String: %s"), *JsonString);

	Request ->ProcessRequest(); 

	// Get Request through API passing in PID

	// If no result found construct new  entry in database

	// If result found return complete struct
	
}

void APersistenceTut_ue5GameMode::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response,
	bool Successful)
{
	if (Successful)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FAILED"));
	}
}
