// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "FGCharacter.h"
#include "BaseNPC.generated.h"

/**
 * 
 */
class USphereComponent;

UCLASS()
class FG_API ABaseNPC : public AFGCharacter
{
	GENERATED_BODY()


public:
	ABaseNPC();

protected:
	virtual void BeginPlay() override;



public:

	virtual void Tick(float DeltaTime) override;

	
	void MoveChar();



};
