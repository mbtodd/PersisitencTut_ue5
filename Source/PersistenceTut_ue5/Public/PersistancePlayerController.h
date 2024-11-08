// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "http.h"
#include "PersistancePlayerController.generated.h"

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()
	UPROPERTY()
	bool isvalid = false;
	UPROPERTY()
	int pid = -1;
	UPROPERTY()
	float Xcoord = 0.0f;
	UPROPERTY()
	float Ycoord = 0.0f;
	UPROPERTY()
	float Zcoord = 0.0f;
};


UCLASS()
class PERSISTENCETUT_UE5_API APersistancePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	APersistancePlayerController();

	virtual void BeginPlay() override;

	void HandleServerEntry();

protected:
	FHttpModule* Http;
	void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful);
	
};
