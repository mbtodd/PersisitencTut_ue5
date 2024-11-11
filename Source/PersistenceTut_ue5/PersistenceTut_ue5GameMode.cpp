// Copyright Epic Games, Inc. All Rights Reserved.

#include "PersistenceTut_ue5GameMode.h"

#include "PersistancePlayerController.h"
#include "UObject/ConstructorHelpers.h"

APersistenceTut_ue5GameMode::APersistenceTut_ue5GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}

void APersistenceTut_ue5GameMode::PostLogin(APlayerController* NewPlayer)
{
	// Super::PostLogin(NewPlayer);

	if (APersistancePlayerController* PC = Cast<APersistancePlayerController>(NewPlayer))
	{
		PC->HandleServerEntry();

	}
}

