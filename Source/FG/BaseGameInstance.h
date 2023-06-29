// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

UENUM(BlueprintType)
enum class CharClass : uint8 {
	Default		UMETA(DisplayName = "Default"),
	Pink		UMETA(DisplayName = "Pink")
};

/**
 * 
 */
UCLASS()
class FG_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Class")
		CharClass characterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Class")
		CharClass P1characterClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Class")
		CharClass P2characterClass;
	
};
