// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PersistenceTut_ue5GameMode.generated.h"

UCLASS(minimalapi)
class APersistenceTut_ue5GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APersistenceTut_ue5GameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
};



