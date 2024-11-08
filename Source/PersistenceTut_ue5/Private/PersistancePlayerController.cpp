// Fill out your copyright notice in the Description page of Project Settings.


#include "PersistancePlayerController.h"

#include "JsonObjectConverter.h"

APersistancePlayerController::APersistancePlayerController()
{
	Http = &FHttpModule::Get();
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

void APersistancePlayerController::HandleServerEntry()
{
	if (!HasAuthority())
	{
		return;
	}



	FString PID = "23";
	
	
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	
	Request ->OnProcessRequestComplete().BindUObject(this, &APersistancePlayerController::OnProcessRequestComplete);
	Request ->SetURL("http://localhost:8080/api/PlayerData/" + PID);
	Request ->SetVerb("GET");
	Request ->SetHeader(TEXT("Content-Type"), "application/json");

	/*FString JsonString;
	FPlayerData PlayerData;
	PlayerData.isvalid = true;
	PlayerData.Xcoord = 121.0f;
	PlayerData.Ycoord = 323.0f;
	PlayerData.Zcoord = 424.0f;
	
	FJsonObjectConverter::UStructToJsonObjectString(PlayerData, JsonString); 
	Request ->SetContentAsString(JsonString);
	UE_LOG(LogTemp, Warning, TEXT("Json String: %s"), *JsonString);*/

	
	// Get Request through API passing in PID

		Request ->ProcessRequest(); 

}

void APersistancePlayerController::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response,
	bool Successful)
{
	if (Successful)
	{
		 // setup pawn
		UE_LOG(LogTemp, Warning, TEXT("SUCCESS %s"), *Response->GetContentAsString());
	}
	else
	{
		// spawn new pawn at default location and create entry in data table
		UE_LOG(LogTemp, Warning, TEXT("FAILED"));
	}
}
