// Fill out your copyright notice in the Description page of Project Settings.


#include "PersistancePlayerController.h"

#include "JsonObjectConverter.h"
#include "PersistenceTut_ue5/PersistenceTut_ue5GameMode.h"


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



	FString PID = "1234";
	
	
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	
	Request ->OnProcessRequestComplete().BindUObject(this, &APersistancePlayerController::OnProcessRequestComplete);
	Request ->SetURL("http://localhost:8080/api/PlayerData/" + PID);
	Request ->SetVerb("GET");
	Request ->SetHeader(TEXT("Content-Type"), "application/json");


	// Get Request through API passing in PID

		Request ->ProcessRequest(); 

}

void APersistancePlayerController::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response,
	bool Successful)
{
	FVector Location = FVector::ZeroVector;
	Location.Z = 400.0f;
	
	if (Successful)
	{
		 // setup pawn
		UE_LOG(LogTemp, Warning, TEXT("SUCCESS %s"), *Response->GetContentAsString());

		FPlayerData PlayerData = ConvertToPlayerData(Response->GetContentAsString());
		if (PlayerData.isvalid)
		{
			UE_LOG(LogTemp, Warning, TEXT("SUCCESS %f"), PlayerData.Zcoord);
		}
		
		if (APersistenceTut_ue5GameMode* GM = GetWorld()->GetAuthGameMode<APersistenceTut_ue5GameMode>())
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			
			if (APawn* NewPawn = GetWorld()->SpawnActor<APawn>(GM->DefaultPawnClass, Location, FRotator::ZeroRotator ,SpawnParameters))
			{
				Possess(NewPawn);
			}
		}
	}
	else
	{
		if (APersistenceTut_ue5GameMode* GM = GetWorld()->GetAuthGameMode<APersistenceTut_ue5GameMode>())
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
			if (APawn* NewPawn = GetWorld()->SpawnActor<APawn>(GM->DefaultPawnClass, Location, FRotator::ZeroRotator ,SpawnParameters))
			{
				Possess(NewPawn);
			}
		}
		// spawn new pawn at default location and create entry in data table
		UE_LOG(LogTemp, Warning, TEXT("FAILED"));
	}
}

FPlayerData APersistancePlayerController::ConvertToPlayerData(const FString& ResponseString)
{
	FPlayerData PlayerData;
	if (ResponseString.Contains("timestamp"))
	{
		FJsonObjectConverter::JsonObjectStringToUStruct(*ResponseString, &PlayerData, 0, 0);
	}

	return PlayerData;
}
