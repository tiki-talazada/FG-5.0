// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FGCharacter.h"
#include "FGGameMode.generated.h"
UENUM(BlueprintType)
enum class EClassChar : uint8 {
	Default		UMETA(DisplayName = "Default"),
	PinkChar	UMETA(DisplayName = "Pink")
};

UCLASS(minimalapi)
class AFGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFGGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player references")
		AFGCharacter* player1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player references")
		AFGCharacter* player2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character class")
		EClassChar className;
};



