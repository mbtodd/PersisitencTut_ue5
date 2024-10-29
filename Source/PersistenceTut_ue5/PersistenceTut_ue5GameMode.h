// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "http.h"
#include "PersistenceTut_ue5GameMode.generated.h"

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()
	UPROPERTY()
	float Xcoord = 0.0f;
	UPROPERTY()
	float Ycoord = 0.0f;
	UPROPERTY()
	float Zcoord = 0.0f;
};

UCLASS(minimalapi)
class APersistenceTut_ue5GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APersistenceTut_ue5GameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

protected:
	FHttpModule* Http;
	void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful);
	
};



